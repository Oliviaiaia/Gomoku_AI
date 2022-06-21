#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <cmath>
#include <string.h>
#include <unordered_map>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class State {
public:
    int Score;
    std::unordered_map<int, State*> discSelectMap;
    State(int s) : Score(s) {}
};

int player, num_disc[3];
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;

                    
const int dir_r[8] = {-1, 0, -1, -1, 1 , 1, 0, 1};
const int dir_c[8] = {0, -1, -1, 1, -1, 1, 1, 0};

int getHashFromPosition(int row, int col) {
    return row * SIZE + col;
}

int getRowFromHash(int hash) {
    return hash / SIZE;
}

int getColFromHash(int hash) {
    return hash % SIZE;
}

bool inBoundary(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

bool isblocked(int row, int col, int t, int py) {
    for(int i = 1 ; i <= 5 ; i++) {
        int nr = row + i*dir_r[t];
        int nc = col + i*dir_c[t];
        if(board[nr][nc] == (3-py) || nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) return true;
    }
    return false;
}

bool formALine(int row, int col, int len, int py) {
    int cont[8] = {0};
    bool retval = false;
    for (int k = 0; k < 8; k++) {
        for (int i = 1; i < len; i++) {
            int nr = dir_r[k]*i + row, nc = dir_c[k]*i + col; 
            if (board[nr][nc] != py) break;
            if (inBoundary(nr, nc) && board[nr][nc] == py) cont[k] ++; 
        }
    }
    for (int k = 0; k < 4; k++) {
        if (cont[k] + cont[7-k] + 1 >= len) retval = true;
    }
    return retval;
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int numberOfLines(int len, int py) {
    int num_lines = 0;
    //horizontal
    for (int i = 0; i < SIZE; i++) {
        int cont = 0;
        bool ignore = false;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == py && ignore == false) cont++;
            else {
                if(board[i][j] == (3 - py) && isblocked(i, j, 6, py)) ignore = true;
                else if(board[i][j] == (3 - py) && !isblocked(i, j, 6, py)) ignore = false;
                if (cont == len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    //vertical
    for (int i = 0; i < SIZE; i++) {
        int cont = 0;
        bool ignore = false;
        for (int j = 0; j < SIZE; j++) {
            if (board[j][i] == py && ignore == false) cont++;
            else {
                if(board[j][i] == (3 - py) && isblocked(j, i, 7, py)) ignore = true;
                else if(board[j][i] == (3 - py) && !isblocked(j, i, 7, py)) ignore = false;
                if (cont == len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    //diagonally(bottom-right)
    for (int k = 0; k < SIZE; k++) {
        int cont = 0;
        bool ignore = false;
        for (int i = 0, j = k; i < SIZE && j < SIZE; i++, j++) {
            if (board[i][j] == py && ignore == false) cont++;
            else {
                if(board[i][j] == (3 - py) && isblocked(i, j, 5, py)) ignore = true;
                else if(board[i][j] == (3 - py) && !isblocked(i, j, 5, py)) ignore = false;
                if (cont >= len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    for (int k = 1; k < SIZE; k++) {
        int cont = 0;
        bool ignore = false;
        for (int i = k, j = 0; i < SIZE && j < SIZE; i++, j++) {
            if (board[i][j] == py && ignore == false) cont++;
            else {
                if(board[i][j] == (3 - py) && isblocked(i, j, 5, py)) ignore = true;
                else if(board[i][j] == (3 - py) && !isblocked(i, j, 5, py)) ignore = false;
                if (cont >= len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    //diagonally(top-right)
    for (int k = SIZE-1; k >= 0; k--) {
        int cont = 0;
        bool ignore = false;
        for (int i = k, j = 0; i >= 0 && j < SIZE; i--, j++) {
            if (board[i][j] == py && ignore == false) cont++;
            else {
                if(board[i][j] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
                else if(board[i][j] == (3 - py) && !isblocked(i, j, 3, py)) ignore = false;
                if (cont == len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    for (int k = 1; k < SIZE-1; k++) {
        int cont = 0;
        bool ignore = false;
        for (int i = SIZE-1, j = k; i >= 0 && j < SIZE; i--, j++) {
            if (board[i][j] == py && ignore == false) cont++;
            else {
                if(board[i][j] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
                else if(board[i][j] == (3 - py) && !isblocked(i, j, 3, py)) ignore = false;
                if (cont == len) num_lines++;
                cont = 0;
            }
        }
        if (cont == len) num_lines++;
    }
    return num_lines;
}


int stateEvaluate( int py) {
    int score = 0;
    for(int i = 3 ; i <= 5 ; i++) {
        score += numberOfLines(i, py) * pow(i, 3);
    } 
    return score;
}


bool isBetterDir(int row, int col, int dir) {
    for(int k = 1 ; k < 5 ; k++) {
        int nr = row + k*dir_r[dir];
        int nc = col + k*dir_c[dir];
        if(!inBoundary(nr, nc)) break;
        if(board[nr][nc] == (3 - player)) return false;
    }
    return true;
}

void getNextMove(State *s, int py) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] != py) continue;
            for(int k = 0 ; k < 8 ; k++) {
                int nr = i + dir_r[k];
                int nc = j + dir_c[k];
                int pos = getHashFromPosition(nr, nc);
                if(s->discSelectMap.find(pos) == s->discSelectMap.end() 
                    && inBoundary(nr, nc) && board[nr][nc] == EMPTY && isBetterDir(nr, nc, k)) {
                    // board[nr][nc] = py;
                    s->discSelectMap[pos] = new State(0);
                    // board[nr][nc] = 0;
                }
            }
            
        }
    }
}

int almostWin(int py) {
    int pos = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j] == EMPTY && formALine(i, j, 4, py)) pos = getHashFromPosition(i, j);
        }
    }
    return pos;
}

int defense_5(int py) {
    int pos = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j] == EMPTY && formALine(i, j, 5, py)) return getHashFromPosition(i, j);
        }
    }
    return pos;
}

int defense_4(int py) {
    int pos = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j] == EMPTY && formALine(i, j, 4, py)) return getHashFromPosition(i, j);
        }
    }
    return pos;
}

int defense_3(int py) {
    int pos = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //if(board[i][j] == EMPTY && formALine(i, j, 4, py)) return getHashFromPosition(i, j);
            if(board[i][j] == EMPTY && formALine(i, j, 3, py)) pos = getHashFromPosition(i, j);
        }
    }
    return pos;
}

int alphabeta(State *s, int depth, int alpha, int beta, int py, bool isplayer) {
    getNextMove(s, py);
    if(depth == 0 || s->discSelectMap.size() == 0) {
        //cout << "depth: " << depth << " score: " << s->Score << "\n";
        s->Score = stateEvaluate(py) * 10 - stateEvaluate(3 - py);
        return s->Score;
    }
    if(isplayer) {
        s->Score = INT_MIN;
        for(auto &next : s->discSelectMap) {
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = py;
            s->Score = max(s->Score, alphabeta(next.second, depth-1, alpha, beta, 3 - py, false));
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = 0;
            alpha = max(alpha, s->Score);
            if(alpha >= beta) break;
        }
    }
    else {
        s->Score = INT_MAX;
        for(auto &next : s->discSelectMap) {
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = py;
            s->Score = min(s->Score, alphabeta(next.second, depth-1, alpha, beta, 3 - py, true));
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = 0;
            beta = min(beta, s->Score);
            if(alpha >= beta) break;
        }
    }
    return s->Score; 
}

void write_valid_spot(std::ofstream& fout) {
    int x, y;
    int max_score = INT_MIN, max_pos = 0;
    if(num_disc[BLACK] == 0 && num_disc[WHITE] == 0) {
        x = SIZE / 2;
        y = SIZE / 2;
    }
    else if(player == WHITE && num_disc[WHITE] == 0) {
        if(board[SIZE / 2][SIZE / 2] == 0) {
            x = SIZE / 2;
            y = SIZE / 2;
        }
        else {
            x = SIZE / 2;
            y = SIZE / 2 + 1;
        }
    } 
    else {
        int pos_at = almostWin(player);
        int pos_df_5 = defense_5(3-player); 
        int pos_df_4 = defense_4(3-player);
        int pos_df_3 = defense_3(3-player);
        if (pos_at >= 0) {
            x = getRowFromHash(pos_at);
            y = getColFromHash(pos_at);
            //cout << "almost win !\n";
        }
        else if(pos_df_5 >= 0) {
            x = getRowFromHash(pos_df_5);
            y = getColFromHash(pos_df_5);
            //cout << "defense 5!\n";
        }
        else if(pos_df_4 >= 0) {
            x = getRowFromHash(pos_df_4);
            y = getColFromHash(pos_df_4);
            //cout << "defense 4!\n";
        }
        else if (pos_df_3 >= 0) {
            x = getRowFromHash(pos_df_3);
            y = getColFromHash(pos_df_3);
            //cout << "defense 3!\n";
        }
        else {
            State *start = new State(0);
            alphabeta(start, 5, INT_MIN, INT_MAX, player, true);            
            for(auto &it : start->discSelectMap) {
                if(it.second->Score >= max_score) {
                    max_pos = it.first;
                    max_score = it.second->Score;
                }
            }
            if(max_score == INT_MIN) {
                x = rand() % SIZE;
                y = rand() % SIZE;
            }
            else {
                x = getRowFromHash(max_pos);
                y = getColFromHash(max_pos);
            }
        }
    }
    //cout << x << " " << y << " " << max_score << " " << best_score << std::endl;
    fout << x << " " << y << std::endl;
    fout.flush();
}

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
            num_disc[board[i][j]] ++;
        }
    }
}
int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}