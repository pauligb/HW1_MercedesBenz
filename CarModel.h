#ifndef CARMODEL_H
#define CARMODEL_H

#include <QQuickItem>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class CarModel : public QQuickItem, public QOpenGLFunctions
{
    Q_OBJECT
public:
    CarModel();

signals:

public slots:

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void sync();
    void paint();

private:
    QSize m_ViewPortSize;
    QOpenGLShaderProgram *m_ShaderProgram;
};

#endif // CARMODEL_H
