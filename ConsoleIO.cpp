#include "ConsoleIO.h"

void ConsoleIO::pause() {
    system("pause");
}

XY ConsoleIO::getMovementPiece() {
    int x, y;
    cout << "Enter the X coordinate of the piece you want to move: ";
    cin >> x;
    cout << "Enter the Y coordinate of the piece you want to move: ";
    cin >> y;
    return XY(x, y);
}

XY ConsoleIO::getMovementTarget() {
    int x, y;
    cout << "Enter the X coordinate you want to move the selected piece to: ";
    cin >> x;
    cout << "Enter the Y coordinate you want to move the selected piece to: ";
    cin >> y;
    return XY(x, y);
}

void ConsoleIO::message(const char* message) {
    cout << message;
}

void ConsoleIO::message(string message) {
    cout << message;
}

XY ConsoleIO::choosePosition(vector<XY>& positions) {
    XY xy;
    for (int i = 0; i < positions.size(); i++) {
        int option = i + 1;
        xy = positions[i];

        ostringstream out;
        out << option << ": (" << xy.getX() << ", " << xy.getY() << ")\n";
        cout << out.str();
    }
    cout << ": ";
    int option = 0;
    while (option <= 0 || option > positions.size()) {
        cin >> option;
    }
    return positions[option - 1];
}
