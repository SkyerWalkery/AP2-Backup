from typing import *
import sys
from PySide6 import QtWidgets, QtGui
from PySide6.QtCore import Qt, QRect, QRunnable, Slot, QThreadPool, QDir, QSize
from PySide6.QtGui import QAction, QPixmap, QMouseEvent, QPainter
from PySide6.QtWidgets import QApplication, QMainWindow, QListWidget, QVBoxLayout, QHBoxLayout, QMenuBar, QMenu, \
    QInputDialog, QLineEdit, QGridLayout, QWidget, QLabel, QPushButton, QFileDialog
import img_rsc


class AreaLabel(QLabel):
    """
    Subclass of QLabel
    Each occupies a place in FieldToolWindow.main_layout
    indicating statement of an area,
    e.g. type(road or grass), direction(e.g. from top to bottom), other flags(start or end of road)
    """

    START_FLAG = 1
    END_FLAG = 2

    def __init__(self, pos: Tuple[int, int], parent: Optional[QWidget] = None):
        super().__init__(parent)
        self.setMinimumSize(QSize(36, 36))
        self.setMaximumSize(QSize(64, 64))
        self.setStyleSheet("border: 2px solid black;")
        self.setAlignment(Qt.AlignCenter)

        default_pixmap = QPixmap(QPixmap(':/images/corner-down-left.svg').size())
        default_pixmap.fill(Qt.transparent)
        self.setPixmap(default_pixmap)

        self.pos: Tuple[int, int] = pos # row and col idx of area
        self.directions = {}
        d = (-1, 0, 1, 0, -1)
        for i in range(4):
            self.directions[(d[i], d[i + 1])] = (0, 0)
        self.area_flag = 0

    def mouseReleaseEvent(self, event: QMouseEvent) -> None:
        input_txt, ok = QInputDialog.getText(
            self,
            'Input attributes of area',
            'Format: (From above) (From below) (From left) (From right) (Start or End)\n'
            'If you do not want to set either one, give a ";"\n'
            'e.g. "b ; ; ; end"',
            QLineEdit.Normal
        )
        if ok and input_txt:
            info = list(input_txt.split())
            if len(info) != 5:
                return

            def char_to_direction(ch: str):
                if ch == ';':
                    return 0, 0
                if 'above'.startswith(ch.lower()):
                    return 0, -1
                if 'below'.startswith(ch.lower()):
                    return 0, 1
                if 'left'.startswith(ch.lower()):
                    return -1, 0
                if 'right'.startswith(ch.lower()):
                    return 1, 0
                raise ValueError('Invalid input')

            self.directions[(0, 1)] = char_to_direction(info[0])
            self.directions[(0, -1)] = char_to_direction(info[1])
            self.directions[(1, 0)] = char_to_direction(info[2])
            self.directions[(-1, 0)] = char_to_direction(info[3])
            if info[4].lower() == 'start':
                self.area_flag = self.START_FLAG
            elif info[4].lower() == 'end':
                self.area_flag = self.END_FLAG
            self.update_pixmap()

    def update_pixmap(self):
        sz = self.pixmap().size()
        new_pixmap = QPixmap(sz)
        new_pixmap.fill(Qt.transparent)
        painter: QPainter = QPainter(new_pixmap)

        # From above
        if self.directions[(0, 1)] == (-1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-down-left.svg'))
        elif self.directions[(0, 1)] == (1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-down-right.svg'))
        elif self.directions[(0, 1)] == (0, 1):
            painter.drawPixmap(0, 0, QPixmap(':/images/arrow-down.svg'))

        # From below
        if self.directions[(0, -1)] == (-1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-up-left.svg'))
        elif self.directions[(0, -1)] == (1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-up-right.svg'))
        elif self.directions[(0, -1)] == (0, -1):
            painter.drawPixmap(0, 0, QPixmap(':/images/arrow-up.svg'))

        # From left
        if self.directions[(1, 0)] == (0, -1):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-right-up.svg'))
        elif self.directions[(1, 0)] == (0, 1):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-right-down.svg'))
        elif self.directions[(1, 0)] == (1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/arrow-right.svg'))

        # From right
        if self.directions[(-1, 0)] == (0, -1):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-left-up.svg'))
        elif self.directions[(-1, 0)] == (0, 1):
            painter.drawPixmap(0, 0, QPixmap(':/images/corner-left-down.svg'))
        elif self.directions[(-1, 0)] == (-1, 0):
            painter.drawPixmap(0, 0, QPixmap(':/images/arrow-left.svg'))

        painter.end()
        self.setPixmap(new_pixmap)

    def to_file_format(self) -> str:
        ret = f'{self.pos[0]} {self.pos[1]} '
        d = (-1, 0, 1, 0, -1)
        for i in range(4):
            x, y = self.directions[(d[i], d[i + 1])]
            ret += f'{x} {y} '
        ret += f'{self.area_flag}'
        return ret

    # If directions are all (0, 0), it shouldn't be written into file
    def should_write(self) -> bool:
        return any((d != (0, 0)) for d in self.directions.values())


class FieldToolWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        menu_bar: QMenuBar = self.menuBar()
        file_menu: QMenu = menu_bar.addMenu('File')
        save_action: QAction = file_menu.addAction('Save')
        save_action.triggered.connect(self.save_as_file)
        load_action: QAction = file_menu.addAction('Load')
        load_action.triggered.connect(self.load_from_file)
        reset_action: QAction = file_menu.addAction('Reset')
        reset_action.triggered.connect(self.reset_field)

        self.num_row = self.num_col = 0
        self.main_layout: QGridLayout = QGridLayout()

        self.central_widget = QWidget()
        self.central_widget.setLayout(self.main_layout)
        self.setCentralWidget(self.central_widget)
        self.setWindowTitle('Field Tool')

    def reset_field(self):
        input_txt, ok = QInputDialog.getText(
            self,
            'Input size of field',
            'e.g. "20 12" means 20 rows * 12 cols',
            QLineEdit.Normal
        )
        if ok and input_txt:
            self.num_row, self.num_col = list(map(int, input_txt.split()))
            self.main_layout: QGridLayout = QGridLayout()
            for i in range(self.num_row):
                for j in range(self.num_col):
                    self.main_layout.addWidget(AreaLabel((i, j)), i, j)
            self.central_widget = QWidget()
            self.central_widget.setLayout(self.main_layout)
            self.setCentralWidget(self.central_widget)

    def save_as_file(self):
        file_info: Tuple[str, str, int] = QFileDialog.getSaveFileName(
            self, "Save File",
            "field.dat",
            "Data (*.dat)"
        )  # Tuple[file directory, filter, length]
        if len(file_info[0]) == 0:
            return

        with open(file_info[0], 'w') as out_file:
            out_file.write(f'{self.num_row} {self.num_col}\n')
            for i in range(self.main_layout.count()):
                area_widget = self.main_layout.itemAt(i).widget()
                if area_widget.should_write():
                    out_file.write(area_widget.to_file_format() + '\n')

    def load_from_file(self):
        file_info: Tuple[str, str, int] = QFileDialog.getOpenFileName(
            self, "Load File",
            "field.dat",
            "Data (*.dat)"
        )  # Tuple[file directory, filter, length]
        if len(file_info[0]) == 0:
            return

        with open(file_info[0], 'r') as in_file:
            self.num_row, self.num_col = map(int, in_file.readline().split())
            roads_idx: Set[Tuple[int, int]] = set()
            self.main_layout: QGridLayout = QGridLayout()
            for line in in_file.readlines():
                info = list(line.split())
                r, c = int(info[0]), int(info[1])
                d = (-1, 0, 1, 0, -1)
                directions = {}
                for i in range(4):
                    directions[(d[i], d[i + 1])] = int(info[i * 2 + 2]), int(info[i * 2 + 3])
                flag = info[10]
                area = AreaLabel((r, c))
                area.directions = directions
                area.area_flag = flag
                area.update_pixmap()
                self.main_layout.addWidget(area, r, c)
                roads_idx.add((r, c))
            for i in range(self.num_row):
                for j in range(self.num_col):
                    if (i, j) not in roads_idx:
                        self.main_layout.addWidget(AreaLabel((i, j)), i, j)
            self.central_widget = QWidget()
            self.central_widget.setLayout(self.main_layout)
            self.setCentralWidget(self.central_widget)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_window = FieldToolWindow()
    main_window.show()
    app.exec()
