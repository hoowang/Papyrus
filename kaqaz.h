#ifndef KAQAZ_H
#define KAQAZ_H

#include <QObject>
#include <QDate>
#include <QStringList>
#include <QSettings>
#include <QScreen>

class Database;
class KaqazPrivate;
class Kaqaz : public QObject
{
    Q_PROPERTY( bool   mobile      READ isMobile      NOTIFY mobileChanged  )
    Q_PROPERTY( bool   tablet      READ isTablet      NOTIFY tabletChanged  )
    Q_PROPERTY( bool   touchDevice READ isTouchDevice NOTIFY touchDeviceChanged )
    Q_PROPERTY( bool   desktop     READ isDesktop     NOTIFY desktopChanged )
    Q_PROPERTY( bool   keyboard    READ keyboard      NOTIFY keyboardChanged )
    Q_PROPERTY( int    currentDays READ currentDays   NOTIFY currentDaysChanged )
    Q_PROPERTY( Qt::LayoutDirection  languageDirection  READ languageDirection NOTIFY languageDirectionChanged )
    Q_PROPERTY(QObject * screen READ screenObj NOTIFY screenChanged)

    Q_OBJECT
public:
    Kaqaz(QObject *parent = 0);
    ~Kaqaz();

    Q_INVOKABLE bool isMobile() const;
    Q_INVOKABLE bool isTablet() const;
    Q_INVOKABLE bool isLargeTablet() const;
    Q_INVOKABLE bool isTouchDevice() const;
    Q_INVOKABLE bool isDesktop() const;
    Q_INVOKABLE bool isMacX() const;
    Q_INVOKABLE bool isWindows() const;
    Q_INVOKABLE bool isLinux() const;
    Q_INVOKABLE bool isAndroid() const;
    Q_INVOKABLE bool isIOS() const;
    Q_INVOKABLE bool isWindowsPhone() const;

    Q_INVOKABLE bool demoHasTrial() const;
    Q_INVOKABLE void demoActiveTrial() const;

    Q_INVOKABLE QString version() const;
    Q_INVOKABLE QString qtVersion() const;
    Q_INVOKABLE QString aboutSialan() const;

    Q_INVOKABLE void deleteFileIfPossible( const QString & id );

    Q_INVOKABLE void removeFile( const QString & path );

    Q_INVOKABLE void setCalendar( int t );
    Q_INVOKABLE QStringList calendarsID() const;
    Q_INVOKABLE QString calendarName( int t );

    Q_INVOKABLE static int currentDays();

    Q_INVOKABLE QString convertIntToStringDate(qint64 d );
    Q_INVOKABLE QString convertIntToFullStringDate(qint64 d );
    Q_INVOKABLE QString convertIntToNumStringDate(qint64 d );
    Q_INVOKABLE QString convertIntToStringDate(qint64 d, const QString & format );

    Q_INVOKABLE void close();
    Q_INVOKABLE void minimize();

    Q_INVOKABLE static Database *database();
    Q_INVOKABLE static QSettings *settings();
    Q_INVOKABLE static QScreen *screen();
    Q_INVOKABLE static QObject *screenObj();

    Q_INVOKABLE void refreshSettings();

    Q_INVOKABLE void setClipboard( const QString & text );
    Q_INVOKABLE QString clipboard() const;

    Q_INVOKABLE QStringList languages();
    Q_INVOKABLE void setCurrentLanguage( const QString & lang );
    Q_INVOKABLE QString currentLanguage() const;

    Q_INVOKABLE static QString resourcePath();

    Q_INVOKABLE void openFile( const QString & address );
    Q_INVOKABLE void share( const QString & subject, const QString & message );
    Q_INVOKABLE void shareToFile( const QString & subject, const QString & message, const QString & path );
    Q_INVOKABLE QString cacheFile( const QString & address );
    Q_INVOKABLE void cleanCache();
    Q_INVOKABLE QString getTempPath();
    Q_INVOKABLE QString getStaticTempPath();

    Q_INVOKABLE static qreal lcdPhysicalSize();
    Q_INVOKABLE static qreal lcdPhysicalWidth();
    Q_INVOKABLE static qreal lcdPhysicalHeight();

    Q_INVOKABLE bool transparentStatusBar();

    Q_INVOKABLE void setProfilePath( QString path );
    Q_INVOKABLE QString profilePath() const;
    Q_INVOKABLE QString repositoryPath() const;
    Q_INVOKABLE QString sdcardPath() const;

    Q_INVOKABLE static qreal lcdDpiX();
    Q_INVOKABLE static qreal lcdDpiY();

    Q_INVOKABLE int densityDpi();
    Q_INVOKABLE qreal density();
    Q_INVOKABLE qreal fontDensity();

    Q_INVOKABLE QString fromMSecSinceEpoch( qint64 t );
    Q_INVOKABLE QString convertDateTimeToString( const QDateTime & dt );

    Q_INVOKABLE static QString passToMd5( const QString & pass );

    Q_INVOKABLE void hideKeyboard();

    Q_INVOKABLE QStringList findBackups();

    Q_INVOKABLE QString fileName( const QString & path );
    Q_INVOKABLE QString fileSuffix( const QString & path );
    Q_INVOKABLE QString readText( const QString & path );

    Q_INVOKABLE void setTutorialCompleted( bool stt );
    Q_INVOKABLE bool isTutorialCompleted() const;

    Q_INVOKABLE bool startCameraPicture();
    Q_INVOKABLE bool getOpenPictures();

    Q_INVOKABLE QString cameraLocation();
    Q_INVOKABLE QString picturesLocation();
    Q_INVOKABLE QString musicsLocation();
    Q_INVOKABLE QString documentsLocation();

    Q_INVOKABLE static QStringList dirEntryFiles(const QString & path , const QStringList &filters);
    Q_INVOKABLE static QStringList findEntryFiles(const QString & path , const QStringList &filters);
    Q_INVOKABLE static QStringList dirEntryDirs(const QString & path);

    Q_INVOKABLE Qt::LayoutDirection languageDirection();

    Q_INVOKABLE void deleteItemDelay( QObject *o, int ms );

    Q_INVOKABLE QStringList getOpenFileNames( const QString & title, const QString & filter );

    Q_INVOKABLE QByteArray encrypt( const QByteArray & ar, const QString & password );
    Q_INVOKABLE QByteArray decrypt( const QByteArray & ar, const QString & password );

    Q_INVOKABLE qreal colorHue( const QColor & clr );
    Q_INVOKABLE qreal colorLightness( const QColor & clr );
    Q_INVOKABLE qreal colorSaturation( const QColor & clr );

    Q_INVOKABLE static QDate convertDaysToDate( int days );
    Q_INVOKABLE static int convertDateToDays( const QDate & date );

    Q_INVOKABLE bool keyboard();

public slots:
    void start();

    void disconnectAllResources();
    void reconnectAllResources();

signals:
    void screenChanged();
    void currentDaysChanged();
    void keyboardChanged();

    void backRequest();
    void languageChanged();
    void languageDirectionChanged();
    void calendarChanged();

    void mobileChanged();
    void tabletChanged();
    void touchDeviceChanged();
    void desktopChanged();

private slots:
    void incomingShare( const QString & title, const QString & msg );
    void incomingImage( const QString & path );
    void selectImageResult( const QString & path );
    void activityPaused();
    void activityResumed();
    void keyboard_changed();

protected:
    void timerEvent(QTimerEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

private:
    void init_languages();

private:
    KaqazPrivate *p;
};

#endif // KAQAZ_H