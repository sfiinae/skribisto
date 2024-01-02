import QtQuick 
import QtQuick.Controls 
import Controller
import Models
import Skribisto
import Writing

MainScreenForm {
    clip: true

    Connections{
        target: UiSignals
        function onChapterCalledFromSideList(chapterId) {
            stack.push(sceneSynopsisPage, {chapterId: chapterId})
        }

    }

    Component {
        id: sceneSynopsisPage
        SceneSynopsisPage{

        }
    }



//    Connections {
//        target: EventDispatcher.chapter()
//        function onCreated(dto) {
//            var chapterDto = dto
//            console.log("dto", chapterDto)
//            console.log("dto.title", chapterDto.title)
//            button.text = chapterDto.title
//        }
//    }

//    Connections {
//        target: button
//        onClicked: {
//            var dto = ChapterController.getCreateChapterDTO()
//            dto.title = "test chapter"

//            ChapterController.create(dto)
//        }
//    }

//    DocumentHandler {
//        quickTextDocument: textArea.textDocument
//        uuid: 1
//    }

//    DocumentHandler {
//        quickTextDocument: textAreaBis.textDocument
//        uuid: 1
//    }

//    DocumentHandler {
//        quickTextDocument: textAreaOther.textDocument
//        uuid: 2
//    }
}
