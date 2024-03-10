#include "stlcreator.h"

#include <libstl_thumb.h>
#include <QFile>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <string>

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(StlCreator, "stlthumbnail.json")

Q_LOGGING_CATEGORY(LOG_STL, "com.stl-thumb-kde")

StlCreator::StlCreator(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

KIO::ThumbnailResult StlCreator::create(const KIO::ThumbnailRequest &request)
{
    const QString path = request.url().toLocalFile();
    std::string path_string = path.toStdString();
    qCWarning(LOG_STL) << "STL-THUMB :: enter library";
    const char* path_cstring = path_string.c_str();
    int width  = request.targetSize().width() * request.devicePixelRatio();
    int height = request.targetSize().height() * request.devicePixelRatio();

    int img_size = width * height * 4;
    img_buf = (uchar *) malloc(img_size);
    if (img_buf == NULL) return KIO::ThumbnailResult::fail();

    if (!render_to_buffer(img_buf, width, height, path_cstring)) {
        qCWarning(LOG_STL) << "STL-THUMB :: lib returned error\n";
        return KIO::ThumbnailResult::fail();
    }

    QImage img = QImage(img_buf,
                 width,
                 height,
                 QImage::Format_RGBA8888,
                 (QImageCleanupFunction) &clean,
                 (void*) this);

//    return true;
    qCWarning(LOG_STL) << "STL-THUMB :: normal exit\n";
    return KIO::ThumbnailResult::pass(img);
}


// Cleanup function provided to QImage to free the buffer after it is done
void clean(void *info)
{
    StlCreator * self = static_cast<StlCreator*>(info);
    free(self->img_buf);
}

#include "stlcreator.moc"
