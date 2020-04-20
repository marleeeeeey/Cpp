#include "PipeConnectionPoint.h"

#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>
#define BUFSIZE 512

std::wstring convertToWString(const std::string & msg)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(msg);
    return wide;
}

struct PipeConnectionPoint::impl {
    BOOL   fConnected = FALSE;
    DWORD  dwThreadId = 0;
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    HANDLE hThread = NULL;
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
        m_status = CpStatus::Connected;
    }
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

    // The pipe connected; change to message-read mode. 
    BOOL   fSuccess = FALSE;
    DWORD dwMode = PIPE_READMODE_MESSAGE;
    fSuccess = SetNamedPipeHandleState(
        m_pimpl->hPipe,             // pipe handle 
        &dwMode,                    // new pipe mode 
        NULL,     // don't set maximum bytes 
        NULL);    // don't set maximum time 
    if (!fSuccess)
    {
        m_logger->LogError("PipeConnectionPoint::connect: SetNamedPipeHandleState failed. GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
    }
}


void PipeConnectionPoint::send(std::string msg)
{ 
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

    if (!fSuccess)
    {
        m_logger->LogError("PipeConnectionPoint::send: WriteFile to pipe failed. GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
    }
}

std::string PipeConnectionPoint::receive()
{
    TCHAR  chBuf[BUFSIZE];
    DWORD  cbRead;
    BOOL fSuccess;
    do
    {
        fSuccess = ReadFile(
            m_pimpl->hPipe,    // pipe handle 
            chBuf,    // buffer to receive reply 
            BUFSIZE * sizeof(TCHAR),  // size of buffer 
            &cbRead,  // number of bytes read 
            NULL);    // not overlapped 

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
            break;

        std::stringstream ss;
        ss << chBuf;
        return ss.str();

    } while (!fSuccess); // repeat loop if ERROR_MORE_DATA 

    if (!fSuccess)
    {
        m_logger->LogError("PipeConnectionPoint::send: ReadFile from pipe failed. GLE=" + std::to_string(GetLastError()));
        m_status = CpStatus::ConnectionError;
    }

    return "";
}

void PipeConnectionPoint::disconnect()
{
    m_status = CpStatus::Disconnected;
    CloseHandle(m_pimpl->hPipe);
}

CpStatus PipeConnectionPoint::getStatus()
{
    return m_status;
}
