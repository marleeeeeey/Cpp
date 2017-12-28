
void testViewSceneItem()
{
    QGraphicsView * view = new QGraphicsView();
    view->show();

    QGraphicsScene * scene = new QGraphicsScene();
    view->setScene(scene);

    QGraphicsItem * item = new QGraphicsLineItem(0, 0, 100, 100);
    scene->addItem(item);
}
