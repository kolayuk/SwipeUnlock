import QtQuick 1.0

Rectangle {
    color:"transparent"
    id:root;
    visible: false
    Component.onCompleted: {player.CheckPlayerState();}
    Connections{
    target:player;
    signal restart;
    onPlayerStarted:{
            root.visible=true;
            progress.anchors.rightMargin=maxlen.width;
            if (pl) {play.visible=true; pause.visible=false;pause.icon="pause";proxy.GetState();}
            else {play.visible=false; pause.visible=true;pause.icon="stop";}
        }
        onPlayerClosed:{root.visible=true;playerwidget.visible=false;}
        onChangeTrackInfo:{songtxt.text=song;artisttxt.text=artist==""?strings[19]:artist;}
        onPlaying:{pause.visible=true;play.visible=false;}
        onPaused:{pause.visible=false;play.visible=true;}
        onStopped:{pause.visible=false;play.visible=true;}
    onChangePos:{
        progress.width=(val/len)*maxlen.width;
        var mins=Math.floor(val/60);
        var secs=val%60;
        time.text=(mins<10?"0"+mins:mins)+":"+(secs<10?"0"+secs:secs);
    }
    }

    Column{
        anchors.right: root.right;
        anchors.left: root.left
        spacing: 10;
        Text{
            id:songtxt
            anchors.right: parent.right
            anchors.rightMargin: 5
            color:m.pressed?"#cc09ba":"white";
            font.pixelSize: 45;
            text:""
            MouseArea{
                id: m
                anchors.fill: parent
                onClicked: {application.Hide(); player.GoToNowPlaying();}

            }
        }
        Text{
            anchors.right: parent.right
            anchors.rightMargin: 5
            id:artisttxt
            color:"white";
            font.pixelSize: 25;
            text:""
        }

        Rectangle{
            id:maxlen;
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.right: parent.right
            anchors.rightMargin: 3;
            height:2;
            color:"white"
            MouseArea{
                anchors.left: parent.left
                anchors.right: parent.right;
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.bottomMargin: -10
                anchors.topMargin: -10;
                onClicked: {
                    var percent=(mouse.x/width)*100;
                    if (percent>100) percent=100;
                    console.log("set pos qml "+percent);
                    proxy.SeekToPos(percent);
                }
            }

            Rectangle{
                id:progress;
                anchors.left: parent.left
                width: 0;
                height:2;
                color:"#1080dd"
        }
        }
        Row{
            anchors.left: parent.left
            anchors.right: parent.right
            Text{
                id:time;
                anchors.left: parent.left
                anchors.leftMargin: 5;
                text:""
                color:"white"
                font.pixelSize: 15;
            }

            Row{
                anchors.right: parent.right
                anchors.rightMargin: 20;
                spacing:5;
                Button{
                    icon:"prev";
                    onPress:{proxy.Previous();}
                    onLongPress:{proxy.SeekBack();}
                    onRelease:{proxy.StopSeeking();}
                }
                Button{
                    visible:true;
                    id:play
                    icon:"play";
                    onPress:{proxy.Play();}
                    onLongPress:{player.ClosePlayer();}
                }
                Button{
                    visible:false;
                    id:pause
                    icon:"pause";
                    onPress:{proxy.Pause();}
                    onLongPress:{player.ClosePlayer();}
                }
                Button{
                    icon:"next";
                    onPress:{proxy.Next();}
                    onLongPress:{proxy.SeekForward();}
                    onRelease:{proxy.StopSeeking();}
                }
            }
        }



    }
}
