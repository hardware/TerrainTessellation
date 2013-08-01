#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QTime>

class AbstractScene;

class QOpenGLContext;

class Window : public QWindow
{
    Q_OBJECT

public:
    Window( QScreen* screen = 0 );

private:
    void initializeGL();

protected slots:
    void resizeGL();
    void paintGL();
    void updateScene();

protected:
    void keyPressEvent( QKeyEvent* e );
    void keyReleaseEvent( QKeyEvent* e );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e );
    void mouseMoveEvent( QMouseEvent* e );

private:
    QOpenGLContext* m_context;
    AbstractScene* m_scene;
    bool m_leftButtonPressed;
    QPoint m_prevPos;
    QPoint m_pos;
    QTime m_time;
};

#endif // WINDOW_H
