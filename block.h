#ifndef MYTEXTURE_H
#define MYTEXTURE_H


#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector>
#include <QVector3D>
#include <QVector2D>

#define CUBE_SIZE 16.0f//每一小个多大

#define TEXTURE_SIZE 256.0f//


class Block : public QOpenGLTexture
{
    //自定义纹理类2023.3.26
public:
    enum BlockType{
        Dirt,
        grass_face//也就是纯绿色的那一面
    };
private:
    QOpenGLFunctions* core;
    QOpenGLVertexArrayObject* VAO;
    QOpenGLBuffer* VBO;
    QOpenGLBuffer* IBO;
    QOpenGLShaderProgram* blockShader;
    QVector2D id;//相对位置
    QVector2D u0v0;//纹理的四个角的坐标
    QVector2D u0v1;
    QVector2D u1v1;
    QVector2D u1v0;
    QVector<float> m_Vertices;//因为只能传入基本类型
    QVector<int> m_Indices;//绘制序号
    bool showUpface = false;
public:
    Block(const QOpenGLWidget*,BlockType,bool isShow = false,const QString& path = ":/textures/texture/blocks.png");
    void draw(const QMatrix4x4& model,const QMatrix4x4& view,const QMatrix4x4& projection);
private:
    void initTexcoord(BlockType);
    void initVertexPos();
    void initShader();
};

#endif // MYTEXTURE_H
