#ifndef _STLCREATOR_H_
#define _STLCREATOR_H_

#include <KIO/ThumbnailCreator>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(LOG_STL)

class StlCreator : public KIO::ThumbnailCreator
{
 Q_OBJECT
public:
    StlCreator(QObject *parent, const QVariantList &args);
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
    uchar *img_buf = NULL;
};

void clean(void *info);

#endif