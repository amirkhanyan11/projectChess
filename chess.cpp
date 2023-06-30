#include <iostream>
#include <string>
#include <cmath>

const int BOARD_SIZE = 8;
bool isWhitekingMoved, isBlackkingMoved, isLeftWhiteRookMoved, isLeftBlackRookMoved, isRightWhiteRookMoved, isRightBlackRookMoved = false;

// Prints the checkboard as you call it
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "     a    b    c    d    e    f    g    h   " << std::endl;
    std::cout << "   +----+----+----+----+----+----+----+----+" << std::endl;
    for (int rank = 0; rank < BOARD_SIZE; ++rank) {
        std::cout << 8 - rank << "  |";
        for (int file = 0; file < BOARD_SIZE; ++file) {
            char piece = board[rank][file];
            std::string pieceUnicode;

            // Basically printing out the pieces by substituting them with Unicode's correspnding chess symbols
            switch (piece) {
                case 'p':  // White Pawn
                    pieceUnicode = "\u2659";
                    break;
                case 'P':  // Black Pawn
                    pieceUnicode = "\u265F";
                    break;
                case 'r':  // White Rook
                    pieceUnicode = "\u2656";
                    break;
                case 'R':  // Black Rook
                    pieceUnicode = "\u265C";
                    break;
                case 'n':  // White Knight
                    pieceUnicode = "\u2658";
                    break;
                case 'N':  // Black Knight
                    pieceUnicode = "\u265E";
                    break;
                case 'b':  // White Bishop
                    pieceUnicode = "\u2657";
                    break;
                case 'B':  // Black Bishop
                    pieceUnicode = "\u265D";
                    break;
                case 'q':  // White Queen
                    pieceUnicode = "\u2655";
                    break;
                case 'Q':  // Black Queen
                    pieceUnicode = "\u265B";
                    break;
                case 'k':  // White King
                    pieceUnicode = "\u2654";
                    break;
                case 'K':  // Black King
                    pieceUnicode = "\u265A";
                    break;
                default:
                    pieceUnicode = " ";
                    break;
            }
            
            std::cout << " " << pieceUnicode << "  |";
        }
        std::cout << std::endl;
        std::cout << "   +----+----+----+----+----+----+----+----+" << std::endl;
    }
}

// Checking the user input in order to find out if it is in proper form(e.g 'c4' or 'f7')
bool isValidPosition(const std::string& position) {
    if(position == "left" || position == "right"){
        return true;
    }
    return (position.length() == 2 && position[0] >= 'a' && position[0] <= 'h' &&
            position[1] >= '1' && position[1] <= '8');
}

// The main logics of the program. All the rules are declared inside of it. Returns true of false, depending on whether the move is appropriate or not in "real chess".
bool isPieceMoveValid(char board[BOARD_SIZE][BOARD_SIZE], const std::string& source, const std::string destination, const std::string& currentPlayer) {
    int sourceRank = 8 - (source[1] - '0');
    int sourceFile = source[0] - 'a';
    int destRank = 8 - (destination[1] - '0');
    int destFile = destination[0] - 'a';

    // Check if the source and destination positions are valid
    if (!isValidPosition(source) || !isValidPosition(destination)) {
        return false;
    }

    // Check if the source position contains a valid piece
    char piece = board[sourceRank][sourceFile];
    if (piece == ' ') {
        return false;
    }

    // Check if the destination position is empty or contains an opponent's piece. Also check if the destination piece is the king. If so, the game ends.
    char destPiece = board[destRank][destFile];

    if ((currentPlayer == "White" && destPiece != ' ' && isupper(destPiece)) || (currentPlayer == "Black" && destPiece != ' ' && islower(destPiece))){
        return false;   // You can't capture your own pieces
    }
    // Check if the piece belongs to the current player. White's pieces are initially declared all uppercase and the black pieces are all decalred lowercase.
    if ((currentPlayer == "White" && islower(piece)) || (currentPlayer == "Black" && isupper(piece))) {
        return false;
    }

    // Checking the movement rules according to the piece
    switch (piece) {
        case 'P':  // White Pawn
            // Move forward
            if (sourceFile == destFile && destPiece == ' ' && ((sourceRank - destRank == 1) || (sourceRank == 6 && sourceRank - destRank == 2))) {
                return true;
            }
            // Capture diagonally
            if ((std::abs(destFile - sourceFile) == 1) && (sourceRank - destRank == 1) && (islower(destPiece))) {
                return true;
            }
            break;
        case 'p':  // Black Pawn
            // Move forward
            if (sourceFile == destFile && destPiece == ' ' && ((destRank - sourceRank == 1) || (sourceRank == 1 && destRank - sourceRank == 2))) {
                return true;
            }
            // Capture diagonally
            if ((std::abs(sourceFile - destFile) == 1) && (sourceRank - destRank == 1) && (isupper(destPiece))) {
                return true;
            }
            break;
        case 'R':  // Rook
        case 'r':
            // Move vertically or horizontally without jumping over other pieces
            if (((destRank != sourceRank && destFile == sourceFile))) {
                int step = (destRank > sourceRank) ? +1 : -1;
                        
                for (int rank = sourceRank + step;(step < 0) ? rank > destRank : rank < destRank; rank += step) {
                    if (board[rank][destFile] != ' ') {
                        return false;  // There's a piece blocking the path
                    }
                }
                if(currentPlayer == "White"){
                    (sourceFile == 0) ? isLeftWhiteRookMoved = true : isRightWhiteRookMoved = true;
                }
                else if(currentPlayer == "Black"){
                    (sourceFile == 0) ? isLeftBlackRookMoved = true : isRightBlackRookMoved = true;
                }
                
                return true;
            }
            if ((destRank == sourceRank && destFile != sourceFile)) {
                int step = (destFile > sourceFile) ? 1 : -1;
                for (int file = sourceFile + step;(step < 0) ? file > destFile : file < destFile; file += step) {
                    if (board[destRank][file] != ' ') {
                        return false;  // There's a piece blocking the path
                    }
                }  
                if(currentPlayer == "White"){
                    (sourceFile == 0) ? isLeftWhiteRookMoved = true : isRightWhiteRookMoved = true;
                }
                else if(currentPlayer == "Black"){
                    (sourceFile == 0) ? isLeftBlackRookMoved = true : isRightBlackRookMoved = true;
                }
                std::cout<<"left or right\n";    
                return true;
            }
            
            break;
        case 'N':  // Knight
        case 'n':
            // Move in Г-shape (2 squares in one direction and 1 square in another)
            if ((std::abs(destRank - sourceRank) == 2 && std::abs(destFile - sourceFile) == 1) || (std::abs(destRank - sourceRank) == 1 && std::abs(destFile - sourceFile) == 2)) {
                return true;
            }
            break;
        case 'B':  // Bishop
        case 'b':
            // Move diagonally without jumping over other pieces
            if (std::abs(destRank - sourceRank) == std::abs(destFile - sourceFile)) {
                int rankStep = (destRank - sourceRank) > 0 ? 1 : -1;
                int fileStep = (destFile - sourceFile) > 0 ? 1 : -1;
                int rank = sourceRank + rankStep;
                int file = sourceFile + fileStep;
                while (rank != destRank) {
                    if (board[rank][file] != ' ') {
                        return false;  // There's a piece blocking the path
                    }
                    rank += rankStep;
                    file += fileStep;
                }
                return true;
            }
            break;
        case 'Q':  // Queen
        case 'q':
            // Move vertically, horizontally, or diagonally without jumping over other pieces
            if ((destRank == sourceRank && destFile != sourceFile) || (destRank != sourceRank && destFile == sourceFile) || std::abs(destRank - sourceRank) == std::abs(destFile - sourceFile)) {
                int rankStep = (destRank - sourceRank) > 0 ? 1 : (destRank - sourceRank) < 0 ? -1 : 0;
                int fileStep = (destFile - sourceFile) > 0 ? 1 : (destFile - sourceFile) < 0 ? -1 : 0;
                int rank = sourceRank + rankStep;
                int file = sourceFile + fileStep;
                while (rank != destRank || file != destFile) {
                    if (board[rank][file] != ' ') {
                        return false;  // There's a piece blocking the path
                    }
                    rank += rankStep;
                    file += fileStep;
                }
                return true;
            }
            break;
        case 'K':  // White King
        case 'k':  // Black King
            // Move one square in any direction
            if (std::abs(destRank - sourceRank) <= 1 && std::abs(destFile - sourceFile) <= 1) {
                (currentPlayer == "White") ? isWhitekingMoved = true : isBlackkingMoved = true;
                return true;
            }
            break;
    }

    return false;
}

bool isKingUnderCheck(char board[BOARD_SIZE][BOARD_SIZE], std::string &opponent){

    std::string currentPlayer = (opponent == "White") ? "Black" : "White";
    int kingRank = 0;
    int kingFile = 0;

    // Find the position of the king
    for (int rank = 0; rank < BOARD_SIZE; ++rank) {
        if (kingRank != 0 && kingFile != 0) {
            break;
        }
        for (int file = 0; file < BOARD_SIZE; ++file) {
            char piece = board[rank][file];
            if ((currentPlayer == "White" && piece == 'k') || (currentPlayer == "Black" && piece == 'K')) {
                kingRank = rank;
                kingFile = file;
            }
        }

    }

    for(int rank = 0; rank < BOARD_SIZE; rank++){
        for(int file = 0; file < BOARD_SIZE; file++){      
            std::string source = std::string(1, file + 'a') + std::to_string(8 - rank); 
            std::string destination = std::string(1, kingFile + 'a') + std::to_string(8 - kingRank);       
            if(isPieceMoveValid(board, source, destination, currentPlayer)){
                return true;
                }                
        }
       }   
    return false;
}

bool castling(char board[BOARD_SIZE][BOARD_SIZE], std::string &currentPlayer, std::string &castleRook){
    std::string opponent = (currentPlayer == "White") ? "Black" : "White";
    if (isKingUnderCheck(board, currentPlayer)){
        std::cout<<"The king is under check.\n";
        return false;
    }
    if (!isValidPosition(castleRook)){
        return false;}
    if((currentPlayer == "White" && isWhitekingMoved) || (currentPlayer == "Black" && isBlackkingMoved)){
        return false;}
    if (currentPlayer == "White" && castleRook == "left" && isLeftWhiteRookMoved){
        std::cout<< "You have already moved your left rook\n";
        return false;
    }
    if (currentPlayer == "White" && castleRook == "right" && isRightWhiteRookMoved){
        std::cout<< "You have already moved your right rook\n";
        return false;
    }   
    if (currentPlayer == "Black" && castleRook == "left" && isLeftBlackRookMoved){
        std::cout<< "You have already moved your left rook\n";
        return false;
    }
    if (currentPlayer == "Black" && castleRook == "right" && isRightBlackRookMoved){
        std::cout<< "You have already moved your right rook\n";
        return false;
    }  
    int rookRank;
    int rookFile;
    int kingFile = 4;
    int step;
    rookRank = (currentPlayer == "White") ? 7 : 0;
    rookFile = (castleRook == "left") ? 0 : 7;
    step = (kingFile > rookFile) ? -1 : 1;
    int kingStep = (kingFile > rookFile) ? -2 : 2;
    for(int index = kingFile + step ;(step < 0) ? index > rookFile : index < rookFile; index += step){
        if(board[rookRank][index] != ' '){
            std::cout <<"There's a piece blocking the path.\n";
            return false;
        }   
    }
    board [rookRank][kingFile] = ' ';
    board [rookRank][rookFile] = ' ';
    board [rookRank][kingFile + kingStep] = (currentPlayer == "White") ? 'K' : 'k';
    board [rookRank][kingFile + kingStep - step] = (currentPlayer == "White") ? 'R' : 'r';
    // std::cout<<board[rookRank][rookFile]<<"\n";
    // std::cout<<board[kingRank][kingFile]<<"\n";
    if(currentPlayer == "White"){
        isWhitekingMoved = true;
        (castleRook == "left") ? isLeftWhiteRookMoved = true : isRightWhiteRookMoved = true;
    }
    if(currentPlayer == "black"){
        isBlackkingMoved = true;
        (castleRook == "left") ? isLeftBlackRookMoved = true : isLeftBlackRookMoved = true;
    }
    return true;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    std::string currentPlayer = "White";
    std::string opponent = (currentPlayer == "White") ? "Black" : "White";
    int checkCount = 0;


    while (true) {
         
        if(!isKingUnderCheck(board, opponent)){
            checkCount = 0;
        }      

        if (isKingUnderCheck(board, opponent)) {
        (checkCount == 0) ? std::cout << "Check! "<< opponent <<" king is under attack." << std::endl : std::cout<<"Mate! "<<currentPlayer<<" wins!\n";
            checkCount++;
        }

        for(int k = 0; k < BOARD_SIZE ; k++){
           if(currentPlayer == "Black" && board[0][k] == 'P'){
            std::string choice;
            std::cout<<"Make a choice(queen or knight): ";
            std::cin >> choice;
            if (choice == "queen"){
                board[0][k] = 'Q';
            } 
            else if (choice == "knight"){
                board[0][k] = 'N';
            }
            break;
           }
           if (currentPlayer == "White" && board[7][k] == 'p'){
            std::string choice;
            std::cout<<"Make a choice(queen or knight): ";
            std::cin >> choice;
            if (choice == "queen"){
                board[7][k] = 'q';
            } 
            else if (choice == "knight"){
                board[7][k] = 'n';
            } 
            break;
           }
        }
        if(checkCount == 2){
        break;
    }  
        std::cout << "\n";
        printBoard(board);
        std::cout << "\n";
        std::cout << currentPlayer << "'s turn" << std::endl;
        std::cout << "\n";

        std::string source, destination, castleRook;
        std::cout << "Enter starting point: ";
        std::cin >> source;
        if(source != "castle"){
        std::cout << "Enter destination point: ";
        std::cin >> destination;}
        else{
            std::cout<<"Choose the Rook: ";
            std::cin >> castleRook;
            if (!castling(board, currentPlayer, castleRook)){
                continue;
            }
            currentPlayer = (currentPlayer == "White") ? "Black" : "White";
            continue;
        }

        if (isPieceMoveValid(board, source, destination, currentPlayer)){
            int sourceRank = 8 - (source[1] - '0');
            int sourceFile = source[0] - 'a';
            int destRank = 8 - (destination[1] - '0');
            int destFile = destination[0] - 'a';

            // Move the piece
            board[destRank][destFile] = board[sourceRank][sourceFile];
            board[sourceRank][sourceFile] = ' ';
            // Switch players
            currentPlayer = (currentPlayer == "White") ? "Black" : "White";
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    return 0;
}


