import QtQuick 1.0
import com.nokia.symbian 1.0
Page{
    anchors.fill: parent;
    Connections{
        target:application
        onAppWorkChanged:{ work.checked=newstate;}
        onAutostartChanged:{autostart.checked=newstate;}
        onPictureChanged:{pic.subTitle=newpic;}
        onHorSenseChanged:{slider.value1=1-sense;}
        onVerSenseChanged:{slider.value2=1-sense;}
        onGestureChanged:{gestures.selectedIndex=newstate;gesture.subTitle=gestures.model[newstate];}
        onZoomChanged:{zooms.selectedIndex=newstate;zoom.subTitle=zooms.model[newstate];}
        onHideSMSChanged:{hidesms.checked=newstate;}
        onNotificationsChanged:{notif.checked=newstate;}
        onPlayerAlbumChanged:{playeralbum.checked=newstate;}
        onUseWallpaperChanged:{usewallpaper.checked=newstate;}
        onFp2DrawChanged:{fp2.checked=newstate;}
        onApp1Changed:{app1.subTitle=app;}
        onApp2Changed:{app2.subTitle=app;}
        onApp3Changed:{app3.subTitle=app;}
        onApp4Changed:{app4.subTitle=app;}
        onApp5Changed:{app5.subTitle=app;}
    }
    signal about;
    QueryDialog{
        id:killdialog;
        message:strings[62]
        titleText: strings[61]
        acceptButtonText: "OK"
        rejectButtonText: strings[45];
        onAccepted:{
            application.KillAnotherLockScreens();
        }
        Component.onCompleted: {
            console.log(lockscreens);
            if (lockscreens>0) killdialog.open();
        }
    }
    Flickable {
        id: flickArea
        //anchors.fill: parent
        anchors.top: statusBar.bottom;
        anchors.bottom: toolBar.top;
        anchors.left: parent.left;
        anchors.right: parent.right
        contentWidth: parent.width; contentHeight: c.height
        flickableDirection: Flickable.VerticalFlick
        clip: true
        Column{
            spacing: 3;
            id:c;
            anchors.right: parent.right
            anchors.left: parent.left
                Text {
                    anchors.leftMargin: 5;
                    id: title
                    anchors.left: parent.left
                    text: "SwipeUnlock"
                    font.pixelSize: 30;
                    font.bold: true;
                    color:"white"
                }
            Row{
                id:r1;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;
                Text{
                    text: strings[20]
                    color:"white"
                    font.pixelSize: 20
                    anchors.verticalCenter: work.verticalCenter
                }
                Switch{
                    id: work;
                    onCheckedChanged:{application.ChangeSetting("appwork",checked);}
                    anchors.right: parent.right
                }
            }
            Row{
                id:r2;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;

                Text{
                    text: strings[21]
                    color:"white"
                    anchors.verticalCenter: autostart.verticalCenter
                    font.pixelSize: 20
                }
                Switch{
                    id: autostart;
                    onCheckedChanged:{application.ChangeSetting("autostart",checked);}
                    //height:key.height-10;
                    anchors.right: parent.right
                }
            }

            Row{
                id:r4;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;
                Text{
                    text: strings[59]
                    color:"white"
                    font.pixelSize: 20
                    anchors.verticalCenter: notif.verticalCenter
                }
                Switch{
                    id: notif;
                    onCheckedChanged:{application.ChangeSetting("notifications",checked);}
                    anchors.right: parent.right
                }
            }

            Row{
                id:r3;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;
                Text{
                    text: strings[57]
                    color:"white"
                    font.pixelSize: 20
                    anchors.verticalCenter: hidesms.verticalCenter
                }
                Switch{
                    id: hidesms;
                    onCheckedChanged:{application.ChangeSetting("hidesms",checked);}
                    anchors.right: parent.right
                }
            }
            Row{
                id:r5;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;
                Text{
                    text: strings[60]
                    color:"white"
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.right: playeralbum.left
                    anchors.verticalCenter: playeralbum.verticalCenter
                }
                Switch{
                    id: playeralbum;
                    onCheckedChanged:{application.ChangeSetting("zplayeralbum",checked);}
                    anchors.right: parent.right
                }
            }

            Row{
                id:r6;
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25;
                anchors.rightMargin: 22;
                Text{
                    text: strings[63]
                    color:"white"
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.right: usewallpaper.left
                    anchors.verticalCenter: usewallpaper.verticalCenter
                }
                Switch{
                    id: usewallpaper;
                    onCheckedChanged:{application.ChangeSetting("zusewallpaper",checked);}
                    anchors.right: parent.right
                }
            }
            SelectionListItem {
                id: pic
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 15;
                anchors.rightMargin: 5;
                title: strings[22]

                onClicked: {application.EditPic();}
                height:usewallpaper.checked?0:zoom.height;
                visible:!usewallpaper.checked
            }
            SelectionListItem {
                id: zoom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 15;
                anchors.rightMargin: 5;
                title: strings[31]
                subTitle: zooms.model[zooms.selectedIndex]
                onClicked: {zooms.open();}
                SelectionDialog {
                    id: zooms
                    titleText: strings[31]
                    model: zoomlist
                    selectedIndex:0
                    onSelectedIndexChanged: {zoom.subTitle=zooms.model[zooms.selectedIndex];application.ChangeSetting("zoom",selectedIndex);}
                }

            }
                SelectionListItem {
                    id: key
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[26]
                    //subTitle: keys.model[keys.selectedIndex]
                    onClicked: {keys.open();}
                    Component.onCompleted: getSubTitle();
                    function getSubTitle(index){
                        var len=application.keysLen();
                        if (len==0) key.subTitle=strings[27];
                        else key.subTitle=len+strings[28];
                        console.log("len:"+keyslist.length);
                    }
                    Component {
                        id: del
                        MyItem{
                            text: modelData
                            selected: application.isKeyChecked(index)
                            onClicked: {
                                selected=!selected;
                                application.checkKey(index,selected);
                                key.getSubTitle();
                            }
                        }
                    }
                    SelectionDialog {
                        //height: (privateStyle.menuItemHeight)*keyslist.length;
                        Component.onCompleted: {content[0].height=privateStyle.menuItemHeight*4.6;}
                        id: keys
                        delegate: del
                        titleText: strings[26]
                        selectedIndex: 0
                        model: keyslist
                        onRejected:application.ChangeSetting("","");
                        onClickedOutside:application.ChangeSetting("","");
                        }

                    }
                SelectionListItem {
                    id: sensevity
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[34]
                    subTitle: ""
                    onClicked: {
                        slider.val1_store=slider.value1;
                        slider.val2_store=slider.value2;
                        slider.open();
                    }
                    SliderDialog{
                        titleText: strings[34]
                        id: slider
                        onAccepted: {
                            application.ChangeSetting("horsense",1-value1);
                            application.ChangeSetting("versense",1-value2);
                            }
                        }
                    }
                SelectionListItem {
                    id: gesture
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[23]
                    subTitle: gestures.model[gestures.selectedIndex]
                    onClicked: {gestures.open();}
                    SelectionDialog {
                        id: gestures
                        titleText: strings[23]
                        model: gesturelist
                        selectedIndex:0
                        onSelectedIndexChanged: {gesture.subTitle=gestures.model[gestures.selectedIndex];application.ChangeSetting("gesture",selectedIndex);}
                        }
                    }
                SelectionListItem {
                    id: app1
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[49]
                    subTitle: app1d.model[app1d.selectedIndex]
                    onClicked: {app1d.open();}
                    AppDialog {
                        id: app1d
                        titleText: strings[49]
                        model: appModel
                        selectedIndex:0
                        onAccepted: {app1.subTitle=app1d.model[app1d.selectedIndex];application.ChangeSetting("app1",selectedIndex);}
                        }
                    }
                SelectionListItem {
                    id: app2
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[50]
                    subTitle: app2d.model[app2d.selectedIndex]
                    onClicked: {app2d.open();}
                    AppDialog {
                        id: app2d
                        titleText: strings[50]
                        model: appModel
                        selectedIndex:0
                        onAccepted: {app2.subTitle=app2d.model[app2d.selectedIndex];application.ChangeSetting("app2",selectedIndex);}
                        }
                    }
                SelectionListItem {
                    id: app3
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[51]
                    subTitle: app3d.model[app3d.selectedIndex]
                    onClicked: {app3d.open();}
                    AppDialog {
                        id: app3d
                        titleText: strings[51]
                        model: appModel
                        selectedIndex:0
                        onAccepted: {app3.subTitle=app3d.model[app3d.selectedIndex];application.ChangeSetting("app3",selectedIndex);}
                        }
                    }
                SelectionListItem {
                    id: app4
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[52]
                    subTitle: app4d.model[app4d.selectedIndex]
                    onClicked: {app4d.open();}
                    AppDialog {
                        id: app4d
                        titleText: strings[52]
                        model: appModel
                        selectedIndex:0
                        onAccepted: {app4.subTitle=app4d.model[app4d.selectedIndex];application.ChangeSetting("app4",selectedIndex);}
                        }
                    }
                SelectionListItem {
                    id: app5
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 5;
                    title: strings[53]
                    subTitle: app5d.model[app5d.selectedIndex]
                    onClicked: {app5d.open();}
                    AppDialog {
                        id: app5d
                        titleText: strings[53]
                        model: appModel
                        selectedIndex:0
                        onAccepted: {app5.subTitle=app5d.model[app5d.selectedIndex];application.ChangeSetting("app5",selectedIndex);}
                        }
                    }
    }
}
    StatusBar {
        id: statusBar
        y:0
        x:0
    }
    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            id: toolBarLayout
            ToolButton {
                flat: true
                id:backbtn;
                iconSource: "toolbar-back.png"
                onClicked: {Qt.quit();}
            }
            ToolButton {
                flat: true
                iconSource: "ovi.png"
                onClicked: {Qt.openUrlExternally("http://store.ovi.com/publisher/Alexander+Fokin/");}
            }
            ToolButton {
                flat: true
                id:aboutbtn;
                iconSource: "toolbar-menu.png"
                onClicked: {about();}
            }
        }
    }
    Component.onCompleted: application.HideSplash();
}
