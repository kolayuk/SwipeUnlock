 import QtQuick 1.1

 Rectangle {
     width:360;
     height:640;
     color: "transparent"
     id:root
     property int coverDisplay: 0;
     Connections{
     target: application;
     onSetToZero:{fl.contentX=root.width; fl.contentY=root.height; launch.margin=launch.height; launch.visible=false;}
     onChangeSize: {
     launch.visible=false;
     launch.margin=launch.height;
         root.height=h;
         root.width=w;
         fl.contentX=root.width;
         fl.contentY=root.height;
     }
     onUpdateWallpaper:{
         console.log("set wallpaper "+wallpaper)
         if (wallpaper.length<9){errtxt.visible=true; errcolor.color="black"; console.log("image error"); errtxt.text=strings[48];}
         else
         {
            if (!coverDisplay) wp.source=wallpaper;
            errtxt.visible=false;
            errcolor.color="transparent";
            console.log("no err in wallpaper");
         }
     }
     }
     Text {
         visible:false;
         id: clockex
         text: clock.hours
         font.pixelSize: 19;
     }

     Connections{
         target: mover;
         onShowLaunchArea:{
             console.log("onShowLaunchArea");
             launch.visible=true;
             launchAnim.to=0;
             launchAnim.start();
             yAnim.to=root.height+launch.height;
             yAnim.start();
         }
     }

     Connections{
     target: player;
     onPlayerStarted:{
     playerwidget.visible=true;
     clock.fontSize=19
     clock.showDate=false
     clock.anchors.right=status.right
     clock.anchors.rightMargin=5
     clock.anchors.bottom=status.top;
     clock.anchors.topMargin=1;
     clock.width=clockex.paintedWidth
     if (!pl)
     {
         coverDisplay=0;
         wp.source=wallpaper;
         playerblack.visible=false;
         wp.fillMode=settings[9]==0?Image.Stretch:Image.PreserveAspectCrop;
     }
     }
     onPlayerClosed:{
     clock.visible=true;
     playerwidget.visible=false;
     clock.fontSize=60
     clock.showDate=true
     clock.anchors.right=status.right
     clock.anchors.rightMargin=5
     clock.anchors.top=wp.top;
     clock.anchors.topMargin=30;
     clock.width=root.width;
     coverDisplay=0;
     wp.source=wallpaper;
     playerblack.visible=false;
         wp.source=wallpaper;
         playerblack.visible=false;
         wp.fillMode=settings[9]==0?Image.Stretch:Image.PreserveAspectCrop;
     }
     onUpdateAlbumArt:{
         if (show&&settings[10]==1) {
         wp.source="image://album/"+Math.random(10);
         playerblack.visible=true;
         //wp.fillMode=Image.PreserveAspectCrop;
             coverDisplay=1;
         wp.fillMode=settings[9]==0?Image.Stretch:Image.PreserveAspectCrop;
         }
         else {
         wp.source=wallpaper;
             coverDisplay=0;
         playerblack.visible=false;
         wp.fillMode=settings[9]==0?Image.Stretch:Image.PreserveAspectCrop;
         }
     }
     }
     NumberAnimation { id:xAnim; target: fl; property: "contentX"; to: 0; duration: 200; easing.type: Easing.OutQuad }
     NumberAnimation { id:yAnim; target: fl; property: "contentY"; to: 0; duration: 200;easing.type: Easing.OutQuad }
     NumberAnimation { id:launchAnim; target: launch; property: "margin"; to: 0; duration: 250;easing.type: Easing.OutQuad
     onRunningChanged: {
      if (!running){
          console.log("anim end, "+to);
          if (to==launch.height&&fl.dy==0) launch.visible=false;
      }
     }
     }
     Flickable{
     id: fl
     property int dx:0;
     property int dy:0;
     anchors.fill: root
     contentWidth: rect.width
     contentHeight: rect.height
     flickDeceleration: 0
     interactive: (!FP2)&&(!launch.visible);
     boundsBehavior: Flickable.StopAtBounds;
     flickableDirection: Flickable.HorizontalAndVerticalFlick
     onMovingChanged: {
         proxy.MovingChanged(moving);
     }
     onMovementEnded: {
         console.log("flick ended "+contentX+" "+contentY);
         if (contentX>(2-settings[5])*root.width)
            {xAnim.to=3*root.width;xAnim.start();}
         else if (contentX<(settings[5])*root.width)
            {xAnim.to=0;xAnim.start();}
         else
            {xAnim.to=root.width;xAnim.start();}
         if (contentY>(2-settings[8])*root.height)
            {yAnim.to=3*root.height;yAnim.start();}
         else if (contentY<(settings[8])*root.height)
            {yAnim.to=0;yAnim.start();}
         else
            {yAnim.to=launch.visible?root.height+launch.height:root.height;yAnim.start();}


         console.log("to: "+xAnim.to+" "+yAnim.to);
         fl.flickableDirection=settings[3]==0?Flickable.HorizontalAndVerticalFlick:settings[3]==1?Flickable.HorizontalFlick:Flickable.VerticalFlick;
     }
     onContentXChanged: {
         dx=root.width-contentX;
         getDirection("X changed");
         if (contentX==0||contentX==3*root.width) {application.Hide();}
         if (dx==0) {fl.flickableDirection=settings[3]==0?Flickable.HorizontalAndVerticalFlick:settings[3]==1?Flickable.HorizontalFlick:Flickable.VerticalFlick;}
     }
     onContentYChanged: {
     dy=root.height-contentY;
     getDirection("Y changed");
     if ((contentY==0||contentY==3*root.height)) {application.Hide();}
     if (dy==0) {fl.flickableDirection=settings[3]==0?Flickable.HorizontalAndVerticalFlick:settings[3]==1?Flickable.HorizontalFlick:Flickable.VerticalFlick}
     }
     function getDirection(func){
     if (Math.abs(dx)>Math.abs(dy)){fl.flickableDirection=Flickable.HorizontalFlick;}
     else {fl.flickableDirection=Flickable.VerticalFlick;}
     }
     onVerticalVelocityChanged: {
         if (verticalVelocity<1&&movingVertically&&dy<0&&Math.abs(dy)<root.height*(1-settings[8])) launchTimer.start();
         else launchTimer.stop();
     }

     Rectangle{
         id:rect
         anchors.centerIn: parent.Center
         width: root.width*3
         height: root.height*3
         color:"transparent"
         Rectangle{
             anchors.centerIn: parent;
             id: errcolor;
             width:root.width;
             height:root.height
             color:"transparent"
             Text {
                 id: errtxt
                 visible: false
                 text: strings[48]
                 font.pixelSize: 20;
                 width: parent.width
                 wrapMode: Text.WordWrap;
                 anchors.centerIn: parent
                 horizontalAlignment: Text.AlignHCenter
                 color:"white"
             }

             Image {
                 id:wp;
                 asynchronous: true;
                 anchors.fill: parent
                 clip:true
                 //source: settings[4];
                 //fillMode: settings[6]==0?Image.Stretch:Image.PreserveAspectCrop
                 sourceSize.height: root.height==640?root.height:0//640;
                 sourceSize.width: root.height==640?0:root.width//360;
                 Component.onCompleted: {
                     fillMode=settings[9]==0?Image.Stretch:Image.PreserveAspectCrop;
                     source=wallpaper;
                     console.log("image ready");
                 }
                 onStatusChanged: {
                 console.log("image status"+wp.status);
                 if (wp.status==Image.Ready) console.log("image ready");
                 if (wp.status==Image.Error||wp.status==Image.Null) {errtxt.visible=true; errcolor.color="black"; console.log("image error"); errtxt.text=strings[48];}
                 else {errtxt.visible=false; errcolor.color="transparent"; console.log("no err in image");}
                 }
             }
             Rectangle{
                 color:"black"
                 id:playerblack
                 visible:false;
                 anchors.fill: parent
                 opacity:0.6
             }

             Notifer{
                 anchors.bottom: wp.bottom;
             }
             StatusBar{
                 id:status
                 rightSide: clock.fontSize==19?clock.width+10:0;
                 anchors.top: wp.top;
                 anchors.left: wp.left
                 anchors.right: wp.right
                 anchors.margins: {left:2; right:2; top:2;}
             }
             DigitalClock{
                 id:clock
                 fontSize:60
                 showDate:true
                 anchors.right: parent.right
                 anchors.rightMargin: 5
                 anchors.top: wp.top;
                 anchors.topMargin: 30;
             }
             Player{
                 id:playerwidget;
                 anchors.right: wp.right
                 //anchors.rightMargin: 10
                 anchors.left: wp.left
                 //anchors.leftMargin: 10;
                 anchors.top: wp.top;
                 anchors.topMargin: 30;
             }
             Rectangle{
                 color:"black"
                 anchors.fill: parent
                 opacity:0.6
                 visible: launch.margin==0
                 MouseArea{
                     anchors.fill:parent
                     onPressed: {
                         console.log("hide launch");
                         launchAnim.to=launch.height;
                         launchAnim.start();
                         yAnim.to=root.height;
                         yAnim.start();
                     }
                 }
             }

             Timer{
                 id: launchTimer
                 interval: 400;
                 running: false;
                 repeat: false
                 onTriggered: {
                     console.log("launch timer triggred");
                 launch.visible=true;
                 launchAnim.to=0;
                 launchAnim.start();
                 yAnim.to=root.height+launch.height;
                 yAnim.start();
                 }
             }

             LaunchArea{
                 id: launch
                 //margin: 100;
                 visible:false;
                 anchors.topMargin: margin
                 anchors.top: wp.bottom;
                 anchors.left: wp.left
                 anchors.right: wp.right
                 color: "black"
                 onVisibleChanged: {
                     if (visible) mover.hide();
                     else mover.show();
                     if (!visible&&fl.dy!=0){
                         launchAnim.to=launch.height;
                         launchAnim.start();
                         yAnim.to=root.height;
                         yAnim.start();
                     }
                 }
             }
         }
     }
     }
 }
