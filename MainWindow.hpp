#pragma once

#include "ClientWrapper.hpp"
#include "html5viewer/html5viewer.h"

#include <QMainWindow>
#include <QSettings>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QTimer>

#define UPDATE_SIGNING_KEY "5gc28hpz1U2BvuCaAtDEUZMFxouH9nwsR9bNaTzqTb1G3vXsQ6"
#define WEB_UPDATES_REPOSITORY "http://bitshares-x.info/"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSettings _settings;
    QMenu* _fileMenu;
    QMenu* _accountMenu;
    QString _deferredUrl;
    QSystemTrayIcon* _trayIcon;

    QByteArray _webPackageSignature;

    QTimer* _updateChecker;
    
  public:
    MainWindow();
    QMenu* fileMenu() { return _fileMenu; }
    QMenu* accountMenu() { return _accountMenu; }

    bool eventFilter(QObject* object, QEvent* event);
    
    ClientWrapper *clientWrapper() const;
    void setClientWrapper(ClientWrapper* clientWrapper);
    void navigateTo(const QString& path);

    bool detectCrash();

public Q_SLOTS:
    void goToMyAccounts();
    void goToAccount(QString accountName);
    void goToCreateAccount();
    void goToAddContact();
    void checkWebUpdates(bool showNoUpdatesAlert = true);
    void loadWebUpdates();

    //Causes this window to attempt to become the front window on the desktop
    void takeFocus();

    void setupTrayIcon();

    ///Used to schedule a custom URL for processing later, once the app has finished starting
    void deferCustomUrl(QString url);
    ///Triggers the deferred URL processign. Call once app has finished starting
    void processDeferredUrl();
    ///Used to process a custom URL now (only call if app has finished starting)
    void processCustomUrl(QString url);
    void goToBlock(uint32_t blockNumber);
    void goToBlock(QString blockId);
    void goToTransaction(QString transactionId);

    void importWallet();

private Q_SLOTS:
    void removeWebUpdates();

private:
    ClientWrapper* _clientWrapper;

    Html5Viewer* getViewer();
    bool walletIsUnlocked(bool promptToUnlock = true);
    std::string getLoginUser(const fc::ecc::public_key& serverKey);
    void doLogin(QStringList components);
    void goToTransfer(QStringList components);
    void readSettings();
    virtual void closeEvent( QCloseEvent* );
    void initMenu();
    void showNoUpdateAlert();
    bool verifyUpdateSignature(QByteArray updatePackage, QByteArray signature); };
