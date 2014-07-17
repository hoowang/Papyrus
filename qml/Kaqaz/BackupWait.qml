import QtQuick 2.2

Item {
    id: backup_wait

    property bool backIsActive: true
    property variant progress

    Connections {
        target: backuper
        onSuccess: backup_wait.success()
        onFailed: backup_wait.failed()
        onProgress: progress.setValue(percent)
    }

    Text {
        id: status_text
        anchors.verticalCenter: backup_wait.verticalCenter
        anchors.left: backup_wait.left
        anchors.right: backup_wait.right
        anchors.margins: 20*physicalPlatformScale
        font.pointSize: 15*fontsScale
        font.family: globalFontFamily
        horizontalAlignment: Text.AlignHCenter
        color: "#333333"
    }

    Timer{
        id: backup_start
        interval: 1000
        repeat: false
        onTriggered: {
            backuper.makeBackup( database.password() )
            backup_wait.backIsActive = false
        }
    }

    Timer{
        id: close_timer
        interval: 1000
        repeat: false
        onTriggered: {
            main.popPreference()
            progress.destroy()
        }
    }

    function back(){
        return !backIsActive
    }

    function success(){
        status_text.text  = qsTr("Done Successfully")
        close_timer.start()
    }

    function failed(){
        status_text.text  = qsTr("Failed!")
        close_timer.start()
    }

    Connections{
        target: kaqaz
        onLanguageChanged: initTranslations()
    }

    function initTranslations(){
        status_text.text  = qsTr("Please Wait")
    }

    Component.onCompleted: {
        initTranslations()
        backup_start.start()
        backHandler = backup_wait
        progress = newModernProgressBar()
    }

    Component.onDestruction: if(progress) progress.destroy()
}