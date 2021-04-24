#include "stlcreator.h"

#include <libstl_thumb.h>
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
    std::string path_string = path.toStdString();
    const char* path_cstring = path_string.c_str();

    int img_size = width * height * 4;
    img_buf = (uchar *) malloc(img_size);
    if (img_buf == NULL) return false;

    if (!render_to_buffer(img_buf, width, height, path_cstring)) {
        qCWarning(LOG_STL) << "STL-THUMB :: lib returned error\n";
        return false;
    }

    img = QImage(img_buf,
                 width,
                 height,
                 QImage::Format_RGBA8888,
                 (QImageCleanupFunction) &clean,
                 (void*) this);

    return true;
}

// Cleanup function provided to QImage to free the buffer after it is done
void clean(void *info)
{
    StlCreator * self = static_cast<StlCreator*>(info);
    free(self->img_buf);
}
