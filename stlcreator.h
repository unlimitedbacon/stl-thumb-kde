#ifndef _STLCREATOR_H_
#define _STLCREATOR_H_

#include <KIO/ThumbCreator>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(LOG_STL)

class StlCreator : public ThumbCreator
{
    public:
        StlCreator();
        ~StlCreator() override;

        bool create(const QString &path, int width, int height, QImage &img) override;

        uchar *img_buf = NULL;
};

void clean(void *info);

#endif