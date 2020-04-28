#include "PipeConnectionPoint.h"
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <locale>
#include <codecvt>
#include <iostream>
#include <mutex>
#include <string>
#define BUFSIZE 512

std::string convertToString(std::wstring s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
    std::string r(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;
}

std::wstring convertToWString(const std::string & s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring r(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
    return r;
}

struct PipeConnectionPoint::impl {
    BOOL   fConnected = FALSE;
    DWORD  dwThreadId = 0;
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    std::mutex pipeMutex;
};

PipeConnectionPoint::PipeConnectionPoint(ILoggerPtr logger)
{
    m_status = CpStatus::ConnectionError;
    m_pimpl = std::make_unique<impl>();
    m_logger = logger;
}

PipeConnectionPoint::~PipeConnectionPoint()
{
    disconnect();
}

void PipeConnectionPoint::accept(ConnectionInfo connectInfo)
{
    std::string lpszPipename = "\\\\.\\pipe\\mynamedpipe";

    m_logger->LogInfo("Pipe Server: Main thread awaiting client connection on " + lpszPipename);
    m_pimpl->hPipe = CreateNamedPipe(
        convertToWString(lpszPipename).c_str(),              // pipe name 
        PIPE_ACCESS_DUPLEX,                     // read/write access 
        PIPE_TYPE_MESSAGE |                     // message type pipe 
        PIPE_READMODE_MESSAGE |                  // message-read mode 
        PIPE_WAIT,                               // blocking mode 
        PIPE_UNLIMITED_INSTANCES,     // max. instances  
        BUFSIZE,                     // output buffer size 
        BUFSIZE,                     // input buffer size 
        0,                         // client time-out 
        NULL);                 // default security attribute 

    if (m_pimpl->hPipe == INVALID_HANDLE_VALUE)
    {
        m_logger->LogError("CreateNamedPipe failed, GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
        return;
    }

    // TODO remove it
    m_pimpl->fConnected = ConnectNamedPipe(m_pimpl->hPipe, NULL) ?
        TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
    
    if(m_pimpl->fConnected)
    {
        m_logger->LogInfo("Client connected. OK");
        m_status = CpStatus::Connected;
    }
}

bool setPipeMode(HANDLE pipe, DWORD mode)
{
    // The pipe connected; change mode. 
    BOOL   fSuccess = FALSE;
    fSuccess = SetNamedPipeHandleState(
        pipe,             // pipe handle 
        &mode,                    // new pipe mode 
        NULL,     // don't set maximum bytes 
        NULL);    // don't set maximum time 
    if (!fSuccess)
    {
        return false;
    }

    return true;
}

void PipeConnectionPoint::connect(ConnectionInfo connectInfo)
{
    std::string lpszPipename = "\\\\.\\pipe\\mynamedpipe";

    m_logger->LogInfo("Connection to server: " + lpszPipename);

    m_pimpl->hPipe = CreateFile(
        convertToWString(lpszPipename).c_str(),              // pipe name 
        GENERIC_READ |  // read and write access 
        GENERIC_WRITE,
        0,              // no sharing 
        NULL,           // default security attributes
        OPEN_EXISTING,  // opens existing pipe 
        0,              // default attributes 
        NULL);          // no template file 

    if (m_pimpl->hPipe == INVALID_HANDLE_VALUE)
    {
        // Exit if an error other than ERROR_PIPE_BUSY occurs. 
        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            m_logger->LogError("PipeConnectionPoint::connect: Could not open pipe. GLE=" + std::to_string(GetLastError()));
            m_status = CpStatus::ConnectionError;
        }

        // All pipe instances are busy, so wait for 20 seconds. 
        if (!WaitNamedPipe(convertToWString(lpszPipename).c_str(), 20000))
        {
            m_logger->LogError("PipeConnectionPoint::connect: Could not open pipe: 20 second wait timed out");
            m_status = CpStatus::ConnectionError;
        }
    }

    m_status = CpStatus::Connected;
    m_logger->LogInfo("Pipe connected successful");
}


void PipeConnectionPoint::send(std::string msg)
{
    std::lock_guard<std::mutex> lg(m_pimpl->pipeMutex);

    setPipeMode(m_pimpl->hPipe, PIPE_WAIT | PIPE_READMODE_BYTE);

    LPCTSTR lpvMessage = convertToWString(msg).c_str();
    DWORD cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
    m_logger->LogInfo("Sending " + std::to_string(cbToWrite) + " byte message: " + msg);
    DWORD  cbWritten;
    BOOL fSuccess = WriteFile(
        m_pimpl->hPipe,                  // pipe handle 
        lpvMessage,             // message 
        cbToWrite,              // message length 
        &cbWritten,             // bytes written 
        NULL);                  // not overlapped 

    if (!fSuccess && GetLastError() != ERROR_NO_DATA)
    {
        m_logger->LogError("PipeConnectionPoint::send: WriteFile to pipe failed. GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
    }

    m_logger->LogTrace("PipeConnectionPoint::send: msg sent. OK");
}

std::string PipeConnectionPoint::receive()
{
    std::lock_guard<std::mutex> lg(m_pimpl->pipeMutex);

    setPipeMode(m_pimpl->hPipe, PIPE_NOWAIT | PIPE_READMODE_BYTE);

    // HANDLE hHeap = GetProcessHeap();
    // TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
    // 
    // DWORD cbBytesRead = 0;
    // HANDLE hPipe = m_pimpl->hPipe;
    // 
    // // Do some extra error checking since the app will keep running even if this
    // // thread fails.
    // LPVOID lpvParam = m_pimpl->hPipe;
    // 
    // if (lpvParam == NULL)
    // {
    //     m_logger->LogError("ERROR - Pipe Server Failure:");
    //     m_logger->LogError("   InstanceThread got an unexpected NULL value in lpvParam.");
    //     if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
    //     m_status = CpStatus::ConnectionError;
    //     return "";
    // }
    // 
    // if (pchRequest == NULL)
    // {
    //     m_logger->LogError("ERROR - Pipe Server Failure:");
    //     m_logger->LogError("   InstanceThread got an unexpected NULL heap allocation.");
    //     m_status = CpStatus::ConnectionError;
    //     return "";
    // }
    // 
    // // Print verbose messages. In production code, this should be for debugging only.
    // //m_logger->LogTrace("InstanceThread created, receiving and processing messages.");
    // 
    // 
    // // Read client requests from the pipe. This simplistic code only allows messages
    // // up to BUFSIZE characters in length.
    // BOOL fSuccess = ReadFile(
    //     hPipe,        // handle to pipe 
    //     pchRequest,    // buffer to receive data 
    //     BUFSIZE * sizeof(TCHAR), // size of buffer 
    //     &cbBytesRead, // number of bytes read 
    //     NULL);        // not overlapped I/O 
    // 
    // if (!fSuccess || cbBytesRead == 0)
    // {
    //     if (GetLastError() == ERROR_BROKEN_PIPE)
    //     {
    //         m_logger->LogError("InstanceThread: client disconnected.");
    //         m_status = CpStatus::ConnectionError;
    //     }
    //     else if(GetLastError() == ERROR_NO_DATA)
    //     {
    //         //m_logger->LogError("InstanceThread ReadFile failed, GLE=" + std::to_string(GetLastError()));
    //     }
    //     else
    //     {
    //         m_logger->LogError("InstanceThread ReadFile failed, GLE=" + std::to_string(GetLastError()));
    //         m_status = CpStatus::ConnectionError;
    //     }
    //     return "";
    // }
    // 
    // std::string retString = convertToString(std::wstring(pchRequest));
    // return retString;







    TCHAR  chBuf[BUFSIZE] = { 0 };
    DWORD  cbRead;
    BOOL fSuccess;
    do
    {
        //m_logger->LogTrace("PipeConnectionPoint::receive: Recieving msg");
        fSuccess = ReadFile(
            m_pimpl->hPipe,    // pipe handle 
            chBuf,    // buffer to receive reply 
            BUFSIZE * sizeof(TCHAR),  // size of buffer 
            &cbRead,  // number of bytes read 
            NULL);    // not overlapped 
    
        if (!fSuccess && (GetLastError() != ERROR_MORE_DATA))
            break;
    
        std::wstring ws(chBuf);
        //m_logger->LogTrace("PipeConnectionPoint::receive: msg received. OK");
        return convertToString(ws);
    
    } while (!fSuccess); // repeat loop if ERROR_MORE_DATA 
    
    if (!fSuccess && GetLastError() != ERROR_NO_DATA)
    {
        m_logger->LogError("PipeConnectionPoint::send: ReadFile from pipe failed. GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
    }
    
    //m_logger->LogTrace("PipeConnectionPoint::receive: msg empty. OK");
    
    return "";
}

void PipeConnectionPoint::disconnect()
{
    m_logger->LogTrace("PipeConnectionPoint::disconnect. OK");
    m_status = CpStatus::Disconnected;
    CloseHandle(m_pimpl->hPipe);
}

CpStatus PipeConnectionPoint::getStatus()
{
    return m_status;
}
