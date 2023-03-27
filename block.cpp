#include "block.h"




Block::Block(const QOpenGLWidget *fa,BlockType bt,bool isShow,const QString& path):
    QOpenGLTexture(QImage(path).mirrored(),QOpenGLTexture::GenerateMipMaps),
    showUpface(isShow)
{
    core = fa->context()->functions();//将当前上下文传递
    initShader();//配置着色器
    initTexcoord(bt);//配置纹理
    initVertexPos();//配置顶点

}

void Block::draw(const QMatrix4x4 &model, const QMatrix4x4& view, const QMatrix4x4 &projection)
{
    blockShader->bind();
    blockShader->setUniformValue("model",model);
    blockShader->setUniformValue("view",view);
    blockShader->setUniformValue("projection",projection);
    VAO->bind();
    this->bind();
    core->glActiveTexture(GL_TEXTURE0);
    //core->glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    core->glDrawArrays(GL_TRIANGLES,0,36);
    VAO->release();
    blockShader->release();
}

void Block::initTexcoord(Block::BlockType bt)
{
    this->setMinMagFilters(QOpenGLTexture::Nearest,QOpenGLTexture::Nearest);
    this->setWrapMode(QOpenGLTexture::Repeat);
    blockShader->bind();
    blockShader->setUniformValue("block_face",0);
    switch (bt) {
        case Block::Dirt:{
            id = QVector2D(2,15);
            break;
        }
    }
    //因为纹理映射是0-1，所以把数据进行转换
    this->u0v0 = QVector2D((id.x()*CUBE_SIZE)/TEXTURE_SIZE,(id.y()*CUBE_SIZE)/TEXTURE_SIZE);
    this->u0v1 = QVector2D((id.x()*CUBE_SIZE)/TEXTURE_SIZE,((id.y()+1)*CUBE_SIZE)/TEXTURE_SIZE);
    this->u1v0 = QVector2D(((id.x()+1)*CUBE_SIZE)/TEXTURE_SIZE,(id.y()*CUBE_SIZE)/TEXTURE_SIZE);
    this->u1v1 = QVector2D(((id.x()+1)*CUBE_SIZE)/TEXTURE_SIZE,((id.y()+1)*CUBE_SIZE)/TEXTURE_SIZE);

}

void Block::initVertexPos()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
         0.5f, -0.5f, -0.5f,  u1v0.x(),u1v0.y(),
         0.5f,  0.5f, -0.5f,  u1v1.x(),u1v1.y(),
         0.5f,  0.5f, -0.5f,  u1v1.x(),u1v1.y(),
        -0.5f,  0.5f, -0.5f,  u0v1.x(),u0v1.y(),
        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),

        -0.5f, -0.5f,  0.5f,  u0v0.x(),u0v0.y(),
         0.5f, -0.5f,  0.5f,  u1v0.x(),u1v0.y(),
         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
        -0.5f,  0.5f,  0.5f,  u1v0.x(),u1v0.y(),
        -0.5f, -0.5f,  0.5f,  u0v0.x(),u0v0.y(),

        -0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
        -0.5f,  0.5f, -0.5f,  u0v1.x(),u0v1.y(),
        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
        -0.5f, -0.5f,  0.5f,  u1v0.x(),u1v0.y(),
        -0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),

         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
         0.5f,  0.5f, -0.5f,  u0v1.x(),u0v1.y(),
         0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
         0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
         0.5f, -0.5f,  0.5f,  u1v0.x(),u1v0.y(),
         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),

        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y(),
         0.5f, -0.5f, -0.5f,  u0v1.x(),u0v1.y(),
         0.5f, -0.5f,  0.5f,  u1v1.x(),u1v1.y(),
         0.5f, -0.5f,  0.5f,  u1v1.x(),u1v1.y(),
        -0.5f, -0.5f,  0.5f,  u1v0.x(),u1v0.y(),
        -0.5f, -0.5f, -0.5f,  u0v0.x(),u0v0.y()
    };
    if(this->showUpface){
        QVector2D tempvec = this->id;
        this->id = QVector2D(8,11);
        //因为纹理映射是0-1，所以把数据进行转换
        this->u0v0 = QVector2D((id.x()*CUBE_SIZE)/TEXTURE_SIZE,(id.y()*CUBE_SIZE)/TEXTURE_SIZE);
        this->u0v1 = QVector2D((id.x()*CUBE_SIZE)/TEXTURE_SIZE,((id.y()+1)*CUBE_SIZE)/TEXTURE_SIZE);
        this->u1v0 = QVector2D(((id.x()+1)*CUBE_SIZE)/TEXTURE_SIZE,(id.y()*CUBE_SIZE)/TEXTURE_SIZE);
        this->u1v1 = QVector2D(((id.x()+1)*CUBE_SIZE)/TEXTURE_SIZE,((id.y()+1)*CUBE_SIZE)/TEXTURE_SIZE);
        this->id = tempvec;
    }
    float upface[] = {
        -0.5f,  0.5f, -0.5f,  u0v0.x(),u0v0.y(),
         0.5f,  0.5f, -0.5f,  u1v0.x(),u1v0.y(),
         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
         0.5f,  0.5f,  0.5f,  u1v1.x(),u1v1.y(),
        -0.5f,  0.5f,  0.5f,  u0v1.x(),u0v1.y(),
        -0.5f,  0.5f, -0.5f,  u0v0.x(),u0v0.y()//此面为上面
    };
    VAO = new QOpenGLVertexArrayObject();
    VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    IBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    VAO->create();
    VBO->create();
    IBO->create();
    VAO->bind();
    VBO->bind();
    IBO->bind();
    VBO->allocate(sizeof (vertices)+sizeof (upface));
    VBO->write(0,vertices,sizeof (vertices));
    VBO->write(sizeof (vertices),upface,sizeof (upface));
    //int pos = blockShader->attributeLocation("aPos");
    blockShader->setAttributeBuffer(0,GL_FLOAT,0,3,5*sizeof(float));
    blockShader->enableAttributeArray(0);
    blockShader->setAttributeBuffer(1,GL_FLOAT,3*sizeof (float),2,5*sizeof(float));
    blockShader->enableAttributeArray(1);
    //IBO->allocate(index,sizeof(index));
    VAO->release();
}

void Block::initShader()
{
    blockShader = new QOpenGLShaderProgram();
    blockShader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shaders/blockvs.glsl");
    blockShader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shaders/blockfs.glsl");
    blockShader->link();
    if(blockShader->isLinked()){
        qDebug()<<"连接成功"<<endl;
    }
}
