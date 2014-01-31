import QtQuick 1.0
import com.nokia.symbian 1.0

CommonDialog {
   id: root
   width: platformContentMaximumWidth
   titleText: strings[55]
   property alias helpText: txt.text
   content:Item {
       height: c.height+10
       width: platformContentMaximumWidth
       Column{
           spacing: 10;
           anchors.left: parent.left;
           anchors.right: parent.right
           anchors.leftMargin: 15;
           anchors.rightMargin: 15;
           id: c;
           anchors.top: parent.top
           anchors.topMargin: 10;
           Text {
               id: txt
               anchors.horizontalCenter: parent.horizontalCenter
               width: parent.width
               horizontalAlignment: Text.AlignJustify
               wrapMode: Text.WordWrap;
               color: "white"
               font.pixelSize: 16
               text: strings[2]
           }
           Button{
               anchors.horizontalCenter: parent.horizontalCenter
               text: "OK"
               width: root.width/2;
               onClicked: root.accept();
           }
       }
     }
   }
