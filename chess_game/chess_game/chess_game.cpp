#include <iostream>
#include <stdlib.h>
#define NOMINMAX
#include <Windows.h>
#include <conio.h> 
#include <vector>
#include <cstdlib>
using namespace std;

bool is_move_possible = false;
bool is_move_possible_2 = false;
vector<string>losted_pieces;
vector<string>losted_pieces_2;
bool player_1 = 0;
bool player_2 = 1;
bool game_over = false;
string piece;

string board[8][8] = {

		{"  r  ", "  n  ", "  b  ", "  q  ", "  k  ", "  b  ", "  n  ", "  r  "},
		{"  p  ", "  p  ", "  p  ", "  p  ", "  p  ", "  p  ", "  p  ", "  p  "},
		{"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "},
		{"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "},
		{"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "},
		{"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "},
		{"  P  ", "  P  ", "  P  ", "  P  ", "  P  ", "  P  ", "  P  ", "  P  "},
		{"  R  ", "  N  ", "  B  ", "  Q  ", "  K  ", "  B  ", "  N  ", "  R  "}
};

void input_control(int& row, int& column) {

	while (true) {

		cout << "\t\t" << "Row : ";  cin >> row;
		cout << "\t\t" << "Column : ";  cin >> column;

		if (cin.fail() || row > 7 || column > 7) { //cin.fail() -> if user input string to int variable it gives error message.cin.fail() helps for avoid infinite loop
			cout << endl << endl;
			cout << "\t\t" << "Please only enter a number between 0 and 7 (0 and 7 include) (dont try to input string or char) !!!" << endl << endl;
			cin.clear();// clearing users input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignores input other than integer.
		}

		else if (board[row][column] == "     ") {

			cout << endl;
			cout << "\t\t" << "Please choose a piece !!!"<<endl<<endl;
		}

		else {

			break;
		}
	}
}

void display_losted_pieces(vector<string>& losted_pieces) {

	int increase = 0;

	for (string& pieces : losted_pieces) {
		
		cout << "\t\t" << increase << "." << pieces;
		increase++;
	}
}

void displayboard() {

	cout << endl << endl;
	cout << "\t" << "          " << "\t" << "                          C  O  L  U  M  N                   " << endl << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "  0      1     2     3     4     5     6     7" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "_________________________________________________" << endl;
	cout << "\t" << "P = Pawn  " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "0  " << "|" << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << "|" << board[0][3] << "|" << board[0][4] << "|" << board[0][5] << "|" << board[0][6] << "|" << board[0][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "B = Bishop" << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << "     2.PLAYER" << "\t\t" << "2.PLAYER Lost These Pieces" << endl;
	cout << "\t" << "          " << "\t" << "      " << "1  " << "|" << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << "|" << board[1][3] << "|" << board[1][4] << "|" << board[1][5] << "|" << board[1][6] << "|" << board[1][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|";  cout << "             ";   display_losted_pieces(losted_pieces_2); cout << endl;
	cout << "\t" << "N = Knight" << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "R     " << "2  " << "|" << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << "|" << board[2][3] << "|" << board[2][4] << "|" << board[2][5] << "|" << board[2][6] << "|" << board[2][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "R = Rook  " << "\t" << "O     " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "3  " << "|" << board[3][0] << "|" << board[3][1] << "|" << board[3][2] << "|" << board[3][3] << "|" << board[3][4] << "|" << board[3][5] << "|" << board[3][6] << "|" << board[3][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "W     " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "K = King  " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "4  " << "|" << board[4][0] << "|" << board[4][1] << "|" << board[4][2] << "|" << board[4][3] << "|" << board[4][4] << "|" << board[4][5] << "|" << board[4][6] << "|" << board[4][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "Q = Queen " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "5  " << "|" << board[5][0] << "|" << board[5][1] << "|" << board[5][2] << "|" << board[5][3] << "|" << board[5][4] << "|" << board[5][5] << "|" << board[5][6] << "|" << board[5][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "6  " << "|" << board[6][0] << "|" << board[6][1] << "|" << board[6][2] << "|" << board[6][3] << "|" << board[6][4] << "|" << board[6][5] << "|" << board[6][6] << "|" << board[6][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << "     1.PLAYER" << "\t\t" << "1.PLAYER Lost These Pieces" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "7  " << "|" << board[7][0] << "|" << board[7][1] << "|" << board[7][2] << "|" << board[7][3] << "|" << board[7][4] << "|" << board[7][5] << "|" << board[7][6] << "|" << board[7][7] << "|";     cout<<"             ";      display_losted_pieces(losted_pieces);   cout << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl << endl;
}

void displayboard_player_2() {

	cout << endl << endl;
	cout << "\t" << "          " << "\t" << "                          C  O  L  U  M  N                   " << endl << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "  0      1     2     3     4     5     6     7" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "_________________________________________________" << endl;
	cout << "\t" << "p = pawn  " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "7  " << "|" << board[7][0] << "|" << board[7][1] << "|" << board[7][2] << "|" << board[7][3] << "|" << board[7][4] << "|" << board[7][5] << "|" << board[7][6] << "|" << board[7][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "b = bishop" << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << "     1.PLAYER" << "\t\t" << "1.PLAYER Lost These Pieces" << endl;
	cout << "\t" << "          " << "\t" << "      " << "6  " << "|" << board[6][0] << "|" << board[6][1] << "|" << board[6][2] << "|" << board[6][3] << "|" << board[6][4] << "|" << board[6][5] << "|" << board[6][6] << "|" << board[6][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|";  cout << "             ";      display_losted_pieces(losted_pieces);    cout << endl;
	cout << "\t" << "n = Knight" << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "R     " << "5  " << "|" << board[5][0] << "|" << board[5][1] << "|" << board[5][2] << "|" << board[5][3] << "|" << board[5][4] << "|" << board[5][5] << "|" << board[5][6] << "|" << board[5][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "r = Rook  " << "\t" << "O     " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "4  " << "|" << board[4][0] << "|" << board[4][1] << "|" << board[4][2] << "|" << board[4][3] << "|" << board[4][4] << "|" << board[4][5] << "|" << board[4][6] << "|" << board[4][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "W     " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "k = King  " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "3  " << "|" << board[3][0] << "|" << board[3][1] << "|" << board[3][2] << "|" << board[3][3] << "|" << board[3][4] << "|" << board[3][5] << "|" << board[3][6] << "|" << board[3][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "q = Queen " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "2  " << "|" << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << "|" << board[2][3] << "|" << board[2][4] << "|" << board[2][5] << "|" << board[2][6] << "|" << board[2][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "1  " << "|" << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << "|" << board[1][3] << "|" << board[1][4] << "|" << board[1][5] << "|" << board[1][6] << "|" << board[1][7] << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << "     2.PLAYER" << "\t\t" << "2.PLAYER Lost These Pieces" << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "     |     |     |     |     |     |     |     " << "|" << endl;
	cout << "\t" << "          " << "\t" << "      " << "0  " << "|" << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << "|" << board[0][3] << "|" << board[0][4] << "|" << board[0][5] << "|" << board[0][6] << "|" << board[0][7] << "|";     cout << "             ";   display_losted_pieces(losted_pieces_2);  cout << endl;
	cout << "\t" << "          " << "\t" << "      " << "   " << "|" << "_____|_____|_____|_____|_____|_____|_____|_____" << "|" << endl << endl;
}

void clear_board(bool &which_player) {

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {

			if (board[i][j] == "  .  ") {

				board[i][j] = "     ";

			}

           if (which_player == 0){

			  if (board[i][j] == "> p <") {

				  board[i][j] = "  p  ";
			  }

			  else if (board[i][j] == "> r <") {

				  board[i][j] = "  r  ";
			  }

			  else if (board[i][j] == "> n <") {

				  board[i][j] = "  n  ";
			  }

			  else if (board[i][j] == "> k <") {

				  board[i][j] = "  k  ";
			  }

			  else if (board[i][j] == "> b <") {

				  board[i][j] = "  b  ";
			  }

			  else if (board[i][j] == "> q <") {

				  board[i][j] = "  q  ";
			  }
		   }

		   else{

			   if (board[i][j] == "> P <") {

				   board[i][j] = "  P  ";
			   }

			   else if (board[i][j] == "> R <") {

				   board[i][j] = "  R  ";
			   }

			   else if (board[i][j] == "> N <") {

				   board[i][j] = "  N  ";
			   }

			   else if (board[i][j] == "> K <") {

				   board[i][j] = "  K  ";
			   }

			   else if (board[i][j] == "> B <") {

				   board[i][j] = "  B  ";
			   }

			   else if (board[i][j] == "> Q <") {

				   board[i][j] = "  Q  ";
			   }
		   }
		}
	}
}

void is_it_target(int& row, int& column, bool &which_player) {

	if (which_player == 0){

		if (board[row][column] == "  p  ") {

			board[row][column] = "> p <";
		}

		else if (board[row][column] == "  r  ") {

			board[row][column] = "> r <";
		}

		else if (board[row][column] == "  n  ") {

			board[row][column] = "> n <";
		}

		else if (board[row][column] == "  k  ") {

			board[row][column] = "> k <";
		}

		else if (board[row][column] == "  b  ") {

			board[row][column] = "> b <";
		}

		else if (board[row][column] == "  q  ") {

			board[row][column] = "> q <";
		}
	}

	else{

		if (board[row][column] == "  P  ") {

			board[row][column] = "> P <";
		}

		else if (board[row][column] == "  R  ") {

			board[row][column] = "> R <";
		}

		else if (board[row][column] == "  N  ") {

			board[row][column] = "> N <";
		}

		else if (board[row][column] == "  K  ") {

			board[row][column] = "> K <";
		}

		else if (board[row][column] == "  B  ") {

			board[row][column] = "> B <";
		}

		else if (board[row][column] == "  Q  ") {

			board[row][column] = "> Q <";
		}
	}
}

void move_to_target_player_1(int& target_row, int& target_column, int& row, int& column,string &piece) {

	if (board[target_row][target_column] == "> p <" || board[target_row][target_column] == "> q <" || board[target_row][target_column] == "> k <" || board[target_row][target_column] == "> b <" || board[target_row][target_column] == "> n <" || board[target_row][target_column] == "> r <" || board[target_row][target_column] == "  .  ") {

		if (board[target_row][target_column] != "  .  ") {

			string add_to_vector = board[target_row][target_column];
			add_to_vector[0] = ' ';
			add_to_vector[4] = ' ';
			losted_pieces_2.push_back(add_to_vector);
		}

		if (board[target_row][target_column] == "> k <"){

			game_over = true;
			cout << "\t\t" << "GAME OVER !!! PLAYER 1 WIN !!! " << endl << endl;
			system("pause");
		}

		is_move_possible = true;
		board[target_row][target_column] = piece;
		board[row][column] = "     ";
		clear_board(player_1);
	}

	else {
		
		cout << "\t\t" << "Invalid Move !!!" << endl << endl;
		cout << "\t\t" << "Try Again Please" << endl << endl;
		Sleep(2000);
	}
}

void move_to_target_player_2(int& target_row, int& target_column, int& row, int& column, string& piece) {

	if (board[target_row][target_column] == "> P <" || board[target_row][target_column] == "> Q <" || board[target_row][target_column] == "> K <" || board[target_row][target_column] == "> B <" || board[target_row][target_column] == "> N <" || board[target_row][target_column] == "> R <" || board[target_row][target_column] == "  .  ") {

		if (board[target_row][target_column] != "  .  ") {

			string add_to_vector = board[target_row][target_column];
			add_to_vector[0] = ' ';
			add_to_vector[4] = ' ';
			losted_pieces.push_back(add_to_vector);
		}

		if (board[target_row][target_column] == "> K <") {

			game_over = true;
			cout << "\t\t" << "GAME OVER !!! PLAYER  WIN !!! " << endl << endl;
			system("pause");
		}

		is_move_possible_2 = true;
		board[target_row][target_column] = piece;
		board[row][column] = "     ";
		clear_board(player_2);
	}

	else {

		cout << "\t\t" << "Invalid Move !!!" << endl << endl;
		cout << "\t\t" << "Try Again Please" << endl << endl;
		Sleep(2000);
	}
}

void pawn_possible_moves(int &row,int &column) {

	if (board[row - 1][column] == "     ") {
		// Boş bir hücreye hareket edebilirsiniz.
		board[row - 1][column] = "  .  ";
		
		if (row == 6) {
			// İlk hamlede iki kare ilerleyebilirsiniz.	
				board[row - 2][column] = "  .  ";
				
		}
		 // Geçerli bir hamle olduğunu işaretleyin.
	}

	if (column > 0 && board[row - 1][column - 1] != "     ") {
		// Sol çaprazda rakip taş varsa, taşı yiyebilirsiniz.
		int sent_row = row - 1;
		int sent_column = column - 1;
		is_it_target(sent_row, sent_column,player_1);
		 // Geçerli bir hamle olduğunu işaretleyin.
	}

	if (column < 7 && board[row - 1][column + 1] != "     ") {
		// Sağ çaprazda rakip taş varsa, taşı yiyebilirsiniz.
		int sentrow = row - 1;
		int sentcolumn = column + 1;
		is_it_target(sentrow, sentcolumn,player_1);
		 // Geçerli bir hamle olduğunu işaretleyin.
	}

}

void pawn_possible_moves_2(int& row, int& column) {

	if (board[row + 1][column] == "     ") {
		// Boş bir hücreye hareket edebilirsiniz.
		board[row + 1][column] = "  .  ";

		if (row == 1) {
			// İlk hamlede iki kare ilerleyebilirsiniz.	
			board[row + 2][column] = "  .  ";
		}
		// Geçerli bir hamle olduğunu işaretleyin.
	}

	if (column > 0 && board[row + 1][column - 1] != "     ") {
		// Sol çaprazda rakip taş varsa, taşı yiyebilirsiniz.

		int sent_row = row + 1;
		int sent_column = column - 1;
		is_it_target(sent_row, sent_column,player_2);
		// Geçerli bir hamle olduğunu işaretleyin.
	}

	if (column < 7 && board[row + 1][column + 1] != "     ") {
		// Sağ çaprazda rakip taş varsa, taşı yiyebilirsiniz.
		int sentrow = row + 1;
		int sentcolumn = column + 1;
		is_it_target(sentrow, sentcolumn,player_2);
		// Geçerli bir hamle olduğunu işaretleyin.
	}
}

void pawn_move(int& target_row, int& target_column , int&row, int&column) {

    piece = "  P  ";
	move_to_target_player_1(target_row, target_column, row, column, piece);

	if (target_row == 0) {

		system("cls");
		displayboard();
		int choice = 0;

		while (true) {

			cout << "\t\t" << "You can replace one piece among the pieces you lost with the pawn . Which piece you want retake ? (PLAYER 1 Lost These Pieces) " << endl << endl;
			cout << "\t\t" << "Number : ";    cin >> choice;

			if (cin.fail()) { //cin.fail() -> if user input string to int variable it gives error message.cin.fail() helps for avoid infinite loop
				cout << endl << endl;
				cout << "\t\t" << "Please only enter a number between 0 and 7 (0 and 7 include) (dont try to input string or char) !!!" << endl << endl;
				cin.clear();// clearing users input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignores input other than integer.
			}

			else if (choice >= 0 && choice <= losted_pieces.size() - 1){

				board[target_row][target_column] = losted_pieces[choice];
				losted_pieces[choice] = "  P  ";
				break;
			}

			else {

				cout << "Please insert a valid number !!! (You can choose a number inside of PLAYER 1 Lost These Pieces)" << endl << endl;
			}
		}
	}	
}

void pawn_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  p  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);

	if (target_row == 7) {

		system("cls");
		displayboard_player_2();
		int choice = 0;

		while (true) {

			cout << "\t\t" << "You can replace one piece among the pieces you lost with the pawn . Which piece you want retake ? (PLAYER 2 Lost These Pieces) " << endl << endl;
			cout << "\t\t" << "Number : ";    cin >> choice;

			if (cin.fail()) { //cin.fail() -> if user input string to int variable it gives error message.cin.fail() helps for avoid infinite loop
				cout << endl << endl;
				cout << "\t\t" << "Please only enter a number (dont try to input string or char) !!!" << endl << endl;
				cin.clear();// clearing users input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignores input other than integer.
			}

			else if (choice >= 0 && choice <= losted_pieces_2.size() - 1) {

				board[target_row][target_column] = losted_pieces_2[choice];
				losted_pieces_2[choice] = "  p  ";
				break;
			}

			else {

				cout << "Please insert a valid number !!! (You can choose a number inside of PLAYER 2 Lost These Pieces)" << endl << endl;
			}
		}
	}
}

void rook_possible_moves_up(int& row, int& column) {

	for (int i = row - 1; i >= 0; i--) {

		if (board[i][column] != "     ") {

			is_it_target(i, column,player_1);

				for (int j = i + 1; j < row; j++) {

					board[j][column] = "  .  ";
				}
			break;
		}

		else if (i == 0) {

			for (int j = row - 1; j >= 0; i--) {

					board[j][column] = "  .  ";
			}
		}	
	}
}

void rook_possible_moves_up_2(int& row, int& column) {

	for (int i = row + 1; i <= 7; i++) {

		if (board[i][column] != "     ") {

			is_it_target(i, column, player_2);

			for (int j = i - 1; j > row; j--) {

				board[j][column] = "  .  ";
			}
			break;
		}

		else if (i == 7) {

			for (int j = row + 1; j <= 7; i++) {

				board[j][column] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_down(int& row, int& column) {

	for (int l = row + 1; l <= 7; l++) {

		if (board[l][column] != "     ") {

			is_it_target(l, column,player_1);

				for (int j = l-1; j > row; j--) {

				  board[j][column] = "  .  ";
				}
			
			break;
		}

		else if (l == 7) {

			for (int j = row + 1; j <= 7; j++) {

				board[j][column] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_down_2(int& row, int& column) {

	for (int l = row - 1; l >= 0; l--) {

		if (board[l][column] != "     ") {

			is_it_target(l, column, player_2);

			for (int j = l + 1; j < row; j++) {

				board[j][column] = "  .  ";
			}

			break;
		}

		else if (l == 0) {

			for (int j = row - 1; j >= 0; j--) {

				board[j][column] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_right(int& row, int& column) {

	for (int m = column + 1; m <= 7; m++) {
	    
		if (board[row][m] != "     ") {

			is_it_target(row, m,player_1);

				for (int j = m-1; j > column; j--) {

				  board[row][j] = "  .  ";
				}

			break;
		}

		else if (m == 7) {

			for (int j = column + 1; j <= 7; j++) {

				board[row][j] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_right_2(int& row, int& column) {

	for (int m = column + 1; m <= 7; m++) {

		if (board[row][m] != "     ") {

			is_it_target(row, m, player_2);

			for (int j = m - 1; j > column; j--) {

				board[row][j] = "  .  ";
			}

			break;
		}

		else if (m == 7) {

			for (int j = column + 1; j <= 7; j++) {

				board[row][j] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_left(int& row, int& column) {

	for (int n = column - 1; n >= 0; n--) {
	
		if (board[row][n] != "     ") {

			is_it_target(row, n,player_1);

        	for (int j = n + 1; j < column; j++) {

					board[row][j] = "  .  ";
			}	
			break;
		}

		else if (n == 0) {

			for (int j = column - 1; j >= 0; j--) {

				board[row][j] = "  .  ";
			}
		}
	}
}

void rook_possible_moves_left_2(int& row, int& column) {

	for (int n = column - 1; n >= 0; n--) {

		if (board[row][n] != "     ") {

			is_it_target(row, n, player_2);

			for (int j = n + 1; j < column; j++) {

				board[row][j] = "  .  ";
			}
			break;
		}

		else if (n == 0) {

			for (int j = column - 1; j >= 0; j--) {

				board[row][j] = "  .  ";
			}
		}
	}
}

void rook_possible_moves(int &row,int &column) {

	rook_possible_moves_up(row,column);
	rook_possible_moves_down(row, column);
	rook_possible_moves_right(row, column);
	rook_possible_moves_left(row, column);		
}

void rook_possible_moves_2(int& row, int& column) {

	rook_possible_moves_up_2(row, column);
	rook_possible_moves_down_2(row, column);
	rook_possible_moves_right_2(row, column);
	rook_possible_moves_left_2(row, column);
}

void rook_move(int& target_row, int& target_column, int& row, int& column) {

	piece = "  R  ";
	move_to_target_player_1(target_row, target_column, row, column,piece);
}

void rook_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  r  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);
}

void bishop_possible_moves(int& row, int& column) {

	bool is_cells_empty = true;

	for (int i = row - 1, j = column + 1; i >= 0 && j < 8; i--,j++) {
	
		if (board[i][j] != "     ") {

			is_it_target(i, j,player_1);

			for (int m = i + 1, n = j - 1; m < row && n >column; m++,n--) {
					
			    board[m][n] = "  .  ";		
			}	
			break;
		}

	    else if (j == 7) {

			for (int m = row - 1, n = column + 1; m >= 0 && n < 8; m--,n++) {

				board[m][n] = "  .  ";
			}
		}	
	}

	for (int m = row - 1, n = column - 1; m >= 0 && n >= 0; m--, n--) {

		if (board[m][n] != "     ") {

			is_it_target(m, n,player_1);

			for (int k = m + 1, l = n + 1; k < row && l <column; k++, l++) {

				board[k][l] = "  .  ";
			}

			break;
		}

		else if (n == 0) {

			for (int k = row - 1, l = column - 1; k >= 0 && l >= 0; k--, l--) {

				board[k][l] = "  .  ";
			}
		}
	}

	for (int x = row + 1, y = column + 1; x <= 7 && y <= 7; x++, y++) {

		if (board[x][y] != "     ") {

			is_it_target(x, y,player_1);

			for (int v = x - 1, z = y - 1; v > row && z > column; v--, z--) {

				board[v][z] = "  .  ";
			}

			break;
		}

		else if( y==7){

			for (int v = row + 1, z = column + 1; v <= 7 && z <= 7; v++, z++) {

				board[v][z] = "  .  ";
			}
		}
	}

	for (int a = row + 1, b = column - 1; a <= 7 && b >= 0; a++, b--) {

		if (board[a][b] != "     ") {

			is_it_target(a, b,player_1);

			for (int c = a - 1, d = b + 1; c > row && d < column; c--, d++) {

				board[c][d] = "  .  ";
			}

			break;
		}

		else if (a == 7){

			for (int c = row + 1, d = column - 1; c <= 7 && d >= 0; c++, d--) {

				board[c][d] = "  .  ";
			}
		}
	}
}

void bishop_possible_moves_2(int& row, int& column) {

	bool is_cells_empty = true;

	for (int i = row + 1, j = column + 1; i <= 7 && j < 8; i++, j++) {

		if (board[i][j] != "     ") {

			is_it_target(i, j, player_2);

			for (int m = i - 1, n = j - 1; m > row && n >column; m--, n--) {

				board[m][n] = "  .  ";
			}
			break;
		}

		else if (j == 7) {

			for (int m = row + 1, n = column + 1; m <= 7 && n < 8; m++, n++) {

				board[m][n] = "  .  ";
			}
		}
	}

	for (int m = row + 1, n = column - 1; m <= 7 && n >= 0; m++, n--) {

		if (board[m][n] != "     ") {

			is_it_target(m, n, player_2);

			for (int k = m - 1, l = n + 1; k > row && l < column; k--, l++) {

				board[k][l] = "  .  ";
			}

			break;
		}

		else if (n == 0) {

			for (int k = row + 1, l = column - 1; k <= 7 && l >= 0; k++, l--) {

				board[k][l] = "  .  ";
			}
		}
	}

	for (int x = row - 1, y = column + 1; x >= 0 && y <= 7; x--, y++) {

		if (board[x][y] != "     ") {

			is_it_target(x, y, player_2);

			for (int v = x + 1, z = y - 1; v < row && z > column; v++, z--) {

				board[v][z] = "  .  ";
			}

			break;
		}

		else if (y == 7) {

			for (int v = row - 1, z = column + 1; v >= 0 && z <= 7; v--, z++) {

				board[v][z] = "  .  ";
			}
		}
	}

	for (int a = row - 1, b = column - 1; a >= 0 && b >= 0; a--, b--) {

		if (board[a][b] != "     ") {

			is_it_target(a, b, player_2);

			for (int c = a + 1, d = b + 1; c < row && d < column; c++, d++) {

				board[c][d] = "  .  ";
			}

			break;
		}

		else if (a == 0) {

			for (int c = row - 1, d = column - 1; c >= 0 && d >= 0; c--, d--) {

				board[c][d] = "  .  ";
			}
		}
	}
}

void bishop_move(int& target_row, int& target_column, int& row, int& column) {

	piece = "  B  ";
	move_to_target_player_1(target_row, target_column, row, column, piece);
}

void bishop_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  b  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);
}

void knight_possible_moves(int&row, int &column) {

	bool can_move = false;
	bool can_move_1 = false;
	bool can_move_2 = false;
	bool can_move_3 = false;
	bool can_move_4 = false;
	bool can_move_5 = false;
	bool can_move_6 = false;
	bool can_move_7 = false;

	if (row - 2 >= 0  && column + 1 < 8) {

		can_move = true;
	}

	auto up_right = [&](){//these are all lambda functions.I use for create function inside function.

			if (board[row - 2][column + 1] != "     ") {

				int sent_row_1 = row - 2;
				int sent_column_1 = column + 1;

				is_it_target(sent_row_1, sent_column_1,player_1);
			}

     		else {

				board[row - 2][column + 1] = "  .  ";
			}
	};  

	if (row - 2 >= 0  && column - 1 >= 0) {

		can_move_1 = true;
	}


	auto up_left = [&](){

			if (board[row - 2][column - 1] != "     ") {

				int sent_row_2 = row - 2;
				int sent_column_2 = column - 1;
				is_it_target(sent_row_2, sent_column_2,player_1);
			}

			else {

				board[row - 2][column - 1] = "  .  ";
			}
	};

	if (row - 1 >= 0 && column - 2 >= 0) {

		can_move_2 = true;
	}

	auto left_up = [&](){

			if (board[row - 1][column - 2] != "     ") {

				int sent_row_3 = row - 1;
				int sent_column_3 = column - 2;
				is_it_target(sent_row_3,sent_column_3,player_1);
			}

			else {

				board[row - 1][column - 2] = "  .  ";
			}
	};

	if ( row + 1 < 8 && column - 2 >= 0) {

		can_move_3 = true;
	}

	auto left_down = [&](){

			if (board[row + 1][column - 2] != "     ") {

				int sent_row_4 = row + 1;
				int sent_column_4 = column - 2;
				is_it_target(sent_row_4, sent_column_4,player_1);
			}

			else {

				board[row + 1][column - 2] = "  .  ";
			}
	};

	if (row - 1 >= 0  &&  column + 2 < 8) {

		can_move_4 = true;
	}

	auto right_up = [&](){

			if (board[row - 1][column + 2] != "     ") {

				int sent_row_5 = row - 1;
				int sent_column_5 = column + 2;
				is_it_target(sent_row_5, sent_column_5,player_1);
			}

			else {

				board[row - 1][column + 2] = "  .  ";
			}
	};

	if ( row + 1 < 8  && column + 2 < 8) {

		can_move_5 = true;
	}

	auto right_down = [&](){

		if (board[row + 1][column + 2] != "     ") {

			int sent_row_6 = row + 1;
			int sent_column_6 = column + 2;
			is_it_target(sent_row_6, sent_column_6,player_1);
		}

		else {

			board[row + 1][column + 2] = "  .  ";
		}
	};

	if (row + 2 < 8 && column + 1 < 8) {

		can_move_6 = true;
	}

	auto down_right = [&]() {

		if (board[row + 2][column + 1] != "     ") {

			int sent_row_7 = row + 2;
			int sent_column_7 = column + 1;
			is_it_target(sent_row_7, sent_column_7,player_1);	
		}

		else {

			board[row + 2][column + 1] = "  .  ";
		}
	};

	if (row + 2 < 8 && column - 1 >= 0) {

		can_move_7 = true;
	}

	auto down_left = [&]() {

		if (board[row + 2][column - 1] != "     ") {

			int sent_row_8 = row + 2;
			int sent_column_8 = column - 1;
			is_it_target(sent_row_8, sent_column_8,player_1);
		}

		else {

			board[row + 2][column - 1] = "  .  ";
		}
	};

	if (can_move == true){

		up_right();	
	}

	if (can_move_1 == true) {

		up_left();
	}

	if (can_move_2 == true) {

		left_up();
	}

	if (can_move_3 == true) {

		left_down();
	}
	
	if (can_move_4 == true) {

		right_up();
	}
	
	if (can_move_5 == true) {

		right_down();
	}

	if (can_move_6 == true) {

		down_right();
	}
	
	if (can_move_7 == true) {

		down_left();
	}		
}

void knight_possible_moves_2(int& row, int& column) {

	bool can_move = false;
	bool can_move_1 = false;
	bool can_move_2 = false;
	bool can_move_3 = false;
	bool can_move_4 = false;
	bool can_move_5 = false;
	bool can_move_6 = false;
	bool can_move_7 = false;

	if (row + 2 < 8 && column + 1 < 8) {

		can_move = true;
	}

	auto up_right = [&]() {//these are all lambda functions.I use for create function inside function.

		if (board[row + 2][column + 1] != "     ") {

			int sent_row_1 = row + 2;
			int sent_column_1 = column + 1;

			is_it_target(sent_row_1, sent_column_1, player_2);
		}

		else {

			board[row + 2][column + 1] = "  .  ";
		}
	};

	if (row + 2 < 8 && column - 1 >= 0) {

		can_move_1 = true;
	}


	auto up_left = [&]() {

		if (board[row + 2][column - 1] != "     ") {

			int sent_row_2 = row + 2;
			int sent_column_2 = column - 1;
			is_it_target(sent_row_2, sent_column_2, player_2);
		}

		else {

			board[row + 2][column - 1] = "  .  ";
		}
	};

	if (row + 1 < 8 && column - 2 >= 0) {

		can_move_2 = true;
	}

	auto left_up = [&]() {

		if (board[row + 1][column - 2] != "     ") {

			int sent_row_3 = row + 1;
			int sent_column_3 = column - 2;
			is_it_target(sent_row_3, sent_column_3, player_2);
		}

		else {

			board[row + 1][column - 2] = "  .  ";
		}
	};

	if (row - 1 >= 0 && column - 2 >= 0) {

		can_move_3 = true;
	}

	auto left_down = [&]() {

		if (board[row - 1][column - 2] != "     ") {

			int sent_row_4 = row - 1;
			int sent_column_4 = column - 2;
			is_it_target(sent_row_4, sent_column_4, player_2);
		}

		else {

			board[row - 1][column - 2] = "  .  ";
		}
	};

	if (row + 1 < 8 && column + 2 < 8) {

		can_move_4 = true;
	}

	auto right_up = [&]() {

		if (board[row + 1][column + 2] != "     ") {

			int sent_row_5 = row + 1;
			int sent_column_5 = column + 2;
			is_it_target(sent_row_5, sent_column_5, player_2);
		}

		else {

			board[row + 1][column + 2] = "  .  ";
		}
	};

	if (row - 1 >= 0 && column + 2 < 8) {

		can_move_5 = true;
	}

	auto right_down = [&]() {

		if (board[row - 1][column + 2] != "     ") {

			int sent_row_6 = row - 1;
			int sent_column_6 = column + 2;
			is_it_target(sent_row_6, sent_column_6, player_2);
		}

		else {

			board[row - 1][column + 2] = "  .  ";
		}
	};

	if (row - 2 >= 0 && column + 1 < 8) {

		can_move_6 = true;
	}

	auto down_right = [&]() {

		if (board[row - 2][column + 1] != "     ") {

			int sent_row_7 = row - 2;
			int sent_column_7 = column + 1;
			is_it_target(sent_row_7, sent_column_7, player_2);
		}

		else {

			board[row - 2][column + 1] = "  .  ";
		}
	};

	if (row - 2 >= 0 && column - 1 >= 0) {

		can_move_7 = true;
	}

	auto down_left = [&]() {

		if (board[row - 2][column - 1] != "     ") {

			int sent_row_8 = row - 2;
			int sent_column_8 = column - 1;
			is_it_target(sent_row_8, sent_column_8, player_2);
		}

		else {

			board[row - 2][column - 1] = "  .  ";
		}
	};

	if (can_move == true) {

		up_right();
	}
	if (can_move_1 == true) {

		up_left();
	}

	if (can_move_2 == true) {

		left_up();
	}

	if (can_move_3 == true) {

		left_down();
	}

	if (can_move_4 == true) {

		right_up();
	}

	if (can_move_5 == true) {

		right_down();
	}

	if (can_move_6 == true) {

		down_right();
	}

	if (can_move_7 == true) {

		down_left();
	}
}

void knight_move(int& target_row, int& target_column, int& row, int& column) {

	piece = "  N  ";
	move_to_target_player_1(target_row, target_column, row, column,piece);
}

void knight_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  n  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);
}

void queen_possible_moves(int &row, int&column){

	bishop_possible_moves(row, column);
	rook_possible_moves(row, column);
}

void queen_possible_moves_2(int& row, int& column) {

	bishop_possible_moves_2(row, column);
	rook_possible_moves_2(row, column);
}

void queen_move(int& target_row, int& target_column, int& row, int& column){

	piece = "  Q  ";
	move_to_target_player_1(target_row, target_column, row, column, piece);
}

void queen_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  q  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);
}

void king_possible_move(int& row, int& column) {

	if (row > 0 && board[row - 1][column] != "     "){//yukarı

		int sent_row_0 = row - 1;
		is_it_target(sent_row_0, column,player_1);
	}
	
	else if(row>0){

		board[row - 1][column] = "  .  ";
	}

	if (column < 7 && row>0 && board[row - 1][column + 1] != "     ") {//sağ yukarı çapraz
		
		int sent_row_1 = row - 1;
		int sent_column_1 = column + 1;
		is_it_target(sent_row_1, sent_column_1,player_1);
	}

	else if (column < 7 && row>0){

		board[row - 1][column + 1] = "  .  ";
	}

	if (row > 0 && column > 0 && board[row - 1][column - 1] != "     ") {//sol yukarı çapraz

		int sent_row_2 = row - 1;
		int sent_column_2 = column - 1;
		is_it_target(sent_row_2, sent_column_2,player_1);
	}

	else if (row > 0 && column > 0) {

		board[row - 1][column - 1] = "  .  ";
	}

	if (column < 7 && board[row][column + 1] != "     "){ //sağ

		int sent_column_3 = column + 1;
		is_it_target(row, sent_column_3,player_1);
	}

	else if (column < 7) {

		board[row][column + 1] = "  .  ";
	}

	if (column > 0 && board[row][column - 1] != "     ") {//sol 

		int sent_column_4 = column - 1;
		is_it_target(row, sent_column_4,player_1);
	}

	else if (column > 0){

		board[row][column - 1] = "  .  ";
	}

	if (row<7 && board[row + 1][column] != "     "){//aşağı

		int sent_row_5 = row + 1;
		is_it_target(sent_row_5, column,player_1);
	}

	else if (row<7){ 

		board[row + 1][column] = "  .  ";
	}
	
	if (column < 7 && row<7 && board[row + 1][column + 1] != "     ") {//sağ aşağı çapraz

		int sent_row_6 = row + 1;
		int sent_column_6 = column + 1;
		is_it_target(sent_row_6, sent_column_6,player_1);
	}

	else if (column < 7 && row < 7){

		board[row + 1][column + 1] = "  .  ";
	}

	if (column > 0 && row<7 && board[row + 1][column - 1] != "     ") {//sol aşağı çapraz

		int sent_row_7 = row + 1;
		int sent_column_7 = column - 1;
		is_it_target(sent_row_7, sent_column_7,player_1);
	}

	else if (column > 0 && row < 7) {

		board[row + 1][column - 1] = "  .  ";
	}
}

void king_possible_move_2(int& row, int& column) {

	if (row < 7 && board[row + 1][column] != "     ") {//yukarı

		int sent_row_0 = row + 1;
		is_it_target(sent_row_0, column, player_2);
	}

	else if (row < 7) {

		board[row + 1][column] = "  .  ";
	}

	if (column < 7 && row<7 && board[row + 1][column + 1] != "     ") {//sağ yukarı çapraz

		int sent_row_1 = row + 1;
		int sent_column_1 = column + 1;
		is_it_target(sent_row_1, sent_column_1, player_2);
	}

	else if (column < 7 && row<7) {

		board[row + 1][column + 1] = "  .  ";
	}

	if (row < 7 && column > 0 && board[row + 1][column - 1] != "     ") {//sol yukarı çapraz

		int sent_row_2 = row + 1;
		int sent_column_2 = column - 1;
		is_it_target(sent_row_2, sent_column_2, player_2);
	}

	else if (row < 7 && column > 0) {

		board[row + 1][column - 1] = "  .  ";
	}

	if (column < 7 && board[row][column + 1] != "     ") { //sağ

		int sent_column_3 = column + 1;
		is_it_target(row, sent_column_3, player_2);
	}

	else if (column < 7) {

		board[row][column + 1] = "  .  ";
	}

	if (column > 0 && board[row][column - 1] != "     ") {//sol 

		int sent_column_4 = column - 1;
		is_it_target(row, sent_column_4, player_2);
	}

	else if (column > 0) {

		board[row][column - 1] = "  .  ";
	}

	if (row > 0 && board[row - 1][column] != "     ") {//aşağı

		int sent_row_5 = row - 1;
		is_it_target(sent_row_5, column, player_2);
	}

	else if (row > 0) {

		board[row - 1][column] = "  .  ";
	}

	if (column < 7 && row > 0 && board[row - 1][column + 1] != "     ") {//sağ aşağı çapraz

		int sent_row_6 = row - 1;
		int sent_column_6 = column + 1;
		is_it_target(sent_row_6, sent_column_6, player_2);
	}

	else if (column < 7 && row > 0) {

		board[row - 1][column + 1] = "  .  ";
	}

	if (column > 0 && row > 0 && board[row - 1][column - 1] != "     ") {//sol aşağı çapraz

		int sent_row_7 = row - 1;
		int sent_column_7 = column - 1;
		is_it_target(sent_row_7, sent_column_7, player_2);
	}

	else if (column > 0 && row > 0) {

		board[row - 1][column - 1] = "  .  ";
	}
}

void king_move(int& target_row, int& target_column, int& row, int& column) {

    piece = "  K  ";
	move_to_target_player_1(target_row, target_column, row, column, piece);
}

void king_move_2(int& target_row, int& target_column, int& row, int& column) {

	piece = "  k  ";
	move_to_target_player_2(target_row, target_column, row, column, piece);
}

void start_game() {

	int row;
	int column;
	int target_row;
	int target_column;

	displayboard();
	cout << "\t\t" << "1.PLAYER TURN" << endl << endl;
	cout << "\t\t" << "Which chess piece you want move ?" << endl << endl;
	input_control(row, column);
	system("cls");

	if (board[row][column] == "  P  ") {
	
		pawn_possible_moves(row, column);
	}

    else if (board[row][column] == "  R  "){

		rook_possible_moves(row, column);
	}

	else if (board[row][column] == "  B  ") {

		bishop_possible_moves(row, column);
		
	}

	else if (board[row][column] == "  N  ") {

		knight_possible_moves(row, column);
	}

	else if (board[row][column] == "  Q  "){

		queen_possible_moves(row, column);
	}

	else if (board[row][column] == "  K  ") {

		king_possible_move(row, column);
	}

	do
	{

		if (is_move_possible == false) {

			system("cls");
		}

		displayboard();
		cout << "\t\t" << "Possible moves on the board as you can see...Your move ?" << endl << endl;
		input_control(target_row, target_column);
		cout << endl;

		if (board[row][column] == "  P  ") {
		
			pawn_move(target_row, target_column,row,column);
		}

		else if (board[row][column] == "  R  ") {

			rook_move(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  B  ") {

			bishop_move(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  N  ") {

			knight_move(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  Q  ") {

			queen_move(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  K  ") {

			king_move(target_row, target_column, row, column);
		}

	} while (is_move_possible == false);

	system("cls");
	displayboard();
	system("cls");

	displayboard_player_2();

	cout << "\t\t" << "2.PLAYER TURN" << endl << endl;
	cout << "\t\t" << "Which chess piece you want move ?" << endl << endl;
	input_control(row, column);
	system("cls");

	if (board[row][column] == "  p  ") {

		pawn_possible_moves_2(row, column);
		
	}

	else if (board[row][column] == "  r  ") {

		rook_possible_moves_2(row, column);
		
	}

	else if (board[row][column] == "  b  ") {

		bishop_possible_moves_2(row, column);
		
	}

	else if (board[row][column] == "  n  ") {

		knight_possible_moves_2(row, column);
		
	}

	else if (board[row][column] == "  q  ") {

		queen_possible_moves_2(row, column);
		
	}

	else if (board[row][column] == "  k  ") {

		king_possible_move_2(row, column);
		
	}

	do
	{
		if (is_move_possible_2 == false) {

			system("cls");
		}

		displayboard_player_2();

		cout << "\t\t" << "Possible moves on the board as you can see...Your move ?" << endl << endl;
		input_control(target_row, target_column);
		cout << endl;

		if (board[row][column] == "  p  ") {

			pawn_move_2(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  r  ") {

			rook_move_2(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  b  ") {

			bishop_move_2(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  n  ") {

			knight_move_2(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  q  ") {

			queen_move_2(target_row, target_column, row, column);
		}

		else if (board[row][column] == "  k  ") {

			king_move_2(target_row, target_column, row, column);
		}

	} while (is_move_possible_2 == false);

	system("cls");
	displayboard_player_2();
	system("cls");
}
 
int main() {

    do{   

		start_game();

	} while (game_over == false);
}

