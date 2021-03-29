#include "stlcreator.h"
//#include "libstl_thumb.h"
#include "stl-thumb/libstl_thumb.h"

#include <QFile>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <string>

Q_LOGGING_CATEGORY(LOG_STL, "com.stl-thumb-kde")

extern "C"
{
    Q_DECL_EXPORT ThumbCreator *new_creator()
    {
        return new StlCreator();
    }
};

StlCreator::StlCreator() = default;

StlCreator::~StlCreator() = default;

bool StlCreator::create(const QString &path, int width, int height, QImage &img)
{
    //qDebug() << "STL-THUMB:: qDegub test";
    std::cout << "STL-THUMB :: Started\n";
    //QImage thumb = QImage( QString("/home/neo/Code/stl-thumb-kde/bacon.png") );
    //img = thumb.scaled(width,height);
    //qDebug() << "STL-THUMB ::" << path;

    std::string path_string = path.toStdString();
    //std::cout << "STL-THUMB :: " << path_string;
    const char* path_cstring = path_string.c_str();
    //qDebug() << "STL-THUMB ::" << path_cstring;

    //printf("%s\n", path_cstring);

    int img_size = width * height * 4;
    //uchar img_buf[img_size] = { 0xff };
    img_buf = (uchar *) malloc(img_size);
    if (img_buf == NULL) return false;

    qCDebug(LOG_STL) << &img_buf;

    if (render_to_buffer(img_buf, width, height, path_cstring)) {
        qCDebug(LOG_STL) << "STL-THUMB :: lib returned true\n";
    } else {
        qCWarning(LOG_STL) << "STL-THUMB :: lib returned error\n";
        return false;
    }

    //uchar* raw_img = render_to_buffer(path_cstring);
    qCDebug(LOG_STL) << &img_buf;
    qCDebug(LOG_STL) << img_buf[0];

    img = QImage( img_buf, width, height, QImage::Format_RGBA8888, (QImageCleanupFunction) &clean, (void*) this);
    // Need to provide cleanup function for image buffer

    //free(img_buf);

    return true;
}

void clean(void *info)
{
    StlCreator * self = static_cast<StlCreator*>(info);
    qCDebug(LOG_STL) << &self->img_buf;
    free(self->img_buf);
    qCDebug(LOG_STL) << "buffer freed\n";
}