import QtQuick 1.0
import com.nokia.symbian 1.0

CommonDialog {
   id: root
   width: platformContentMaximumWidth
   titleText: "Slider"
   property alias value1: sl1.value
   property alias value2: sl2.value
   property real val1_store: sl1.value
   property real val2_store: sl2.value
   content:Item {
     id: name
     height: c.height+10
     width: parent.width
     Column{
         width: parent.width
         id:c
         anchors.top: parent.top
         anchors.topMargin: 5;
         spacing: 0
         MySlider{
         id: sl1
             title: strings[46]
             min: strings[35]
             max: strings[36]
         }
         MySlider{
             id:sl2
             title: strings[47]
             min: strings[35]
             max: strings[36]
         }
         Rectangle{
         height:10
         width: parent.width
         color: "transparent"
         }

         ButtonRow {
               id:b
               exclusive: false
               checkedButton: root
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.bottom: parent.bottom;
               //anchors.bottomMargin: 5;
               anchors.left: parent.left
               anchors.leftMargin: 40;
               anchors.right: parent.right
               anchors.rightMargin: 40
               Button {text: "OK"; onClicked: root.accept();}
               Button {
               text: strings[45];
                onClicked: {
                    sl1.value=root.val1_store;
                    sl2.value=root.val2_store;
                    root.close();
                }
                }
              }
     }
   }
   }
