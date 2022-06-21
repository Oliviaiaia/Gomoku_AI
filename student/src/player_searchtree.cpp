// #include <iostream>
// #include <fstream>
// #include <cstdlib>
// #include <ctime>
// #include <array>
// #include <cmath>
// #include <string.h>
// #include <unordered_map>
// #include <climits>
// #include <algorithm>
// using namespace std;

// enum SPOT_STATE {
//     EMPTY = 0,
//     BLACK = 1,
//     WHITE = 2
// };

// class State {
// public:
//     //std::array<std::array<int, SIZE>, SIZE> board;
//     int Score;
//     int Oppo_horizontal[4], Oppo_vertical[4], Oppo_bottom_right[4], Oppo_top_right[4]; 
//     std::unordered_map<int, State*> discSelectMap;
//     State(int s) : Score(s) {
//         Oppo_horizontal[4] = {0}; //[0] : row, [1] : col, [2] : the number of continuous discs(>=3)
//         Oppo_vertical[4] = {0};
//         Oppo_bottom_right[4] = {0};
//         Oppo_top_right[4] = {0};
//     }
// };

// int player;
// const int SIZE = 15;
// std::array<std::array<int, SIZE>, SIZE> board;


// //                   [h][v][br][tr]  
// const int dir_r[8] = {0, 1, 1, -1, 0, -1, -1, 1};
// const int dir_c[8] = {1, 0, 1, 1, -1, 0, -1, -1};



// void read_board(std::ifstream& fin) {
//     fin >> player;
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             fin >> board[i][j];
//         }
//     }
// }

// // int continuousPieces( int row, int col, int type, int py) {
// //     int pieces = 0;
// //     if(type == 0) {
// //         for(int i = col ; i < SIZE ; i++) {
// //             if(board[row][i] != py && pieces != 1) return pieces;
// //             if(board[row][i] != py && pieces == 1) return 0;
// //             pieces++;
// //         }
// //     }
// //     if(type == 1) {
// //         for(int i = row ; i < SIZE ; i++) {
// //             if(board[i][col] != py && pieces != 1) return pieces;
// //             if(board[i][col] != py && pieces == 1) return 0;
// //             pieces++;
// //         }
// //     }
// //     if(type == 2) {
// //         for(int i = row, j = col ; i < SIZE && j < SIZE ; i++, j++) {
// //             if(board[i][j] != py && pieces != 1) return pieces;
// //             if(board[i][j] != py && pieces == 1) return 0;
// //             pieces++;
// //         }
// //     }
// //     if(type == 3) {
// //         for(int i = row, j = col ; i >= 0 && j < SIZE ; i--, j++) {
// //             if(board[i][j] != py && pieces != 1) return pieces;
// //             if(board[i][j] != py && pieces == 1) return 0;
// //             pieces++;
// //         }
// //     }
// //     return 0;
// // }

// // bool exceedBoard(int row, int col, int t) {
// //     int nr = row + 4*dir_r[t];
// //     int nc = col + 4*dir_c[t];
// //     if(nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) return false;
// //     else return true;
// // }



// void stateEvaluate_check(int py) {
//     int score = 0;
//     //vertical
//     for(int i = 0 ; i < SIZE ; i++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[j][i] == py && ignore == false) cnt++;
//             if(board[j][i] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(j, i, 1, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(j, i, 1, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }    
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     cout << "vertical score = " << score << endl;
//     score = 0;
//     // for(int i = 0 ; i < SIZE ; i++) {
//     //     int cnt = 0;
//     //     for(int j = 0 ; j < SIZE ; j++) {
//     //         if(board[j][i] == py) cnt++;
//     //         if(board[j][i] != py) {
//     //             if(cnt >= 3) score++;
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++; 
//     // }
//     // cout << "vertical score = " << score << endl;
//     // score = 0;
//     //horizontal
//     // for(int i = 0 ; i < SIZE ; i++) {
//     //     int cnt = 0;
//     //     for(int j = 0 ; j < SIZE ; j++) {
//     //         if(board[i][j] == py) cnt++;
//     //         if(board[i][j] != py) {
//     //             if(cnt >= 3) score++; 
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++; 
//     // }
//     for(int i = 0 ; i < SIZE ; i++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 0, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 0, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     cout << "horizontal score = " << score << endl;
//     score = 0;
//     //diagonally(bottom-right)
//     // for(int k = 0 ; k < SIZE ; k++) {
//     //     int cnt = 0;
//     //     for(int i = 0, j = k ; i < SIZE && j < SIZE ; i++, j++) {
//     //         if(board[i][j] == py) cnt++;
//     //         if(board[i][j] != py) {
//     //             if(cnt >= 3) score++; 
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++; 
//     // }
//     // for(int k = 1 ; k < SIZE ; k++) {
//     //     int cnt = 0;
//     //     for(int i = k, j = 0 ; i < SIZE && j < SIZE ; i++, j++) {
//     //         if(board[i][j] == py) cnt++;
//     //         if(board[i][j] != py) {
//     //             if(cnt >= 3) score++; 
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++; 
//     // }
//     for(int k = 0 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = 0, j = k ; i < SIZE && j < SIZE ; i++, j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 2, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 2, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     for(int k = 1 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = k, j = 0 ; i < SIZE && j < SIZE ; i++, j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 2, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 2, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     cout << "bottom-right score = " << score << endl;
//     score = 0;
//     // . . . o
//     // o o o .
//     // . . o .
//     // . . o o
//     //diagonally(top-right)
//     // for(int k = 0 ; k < SIZE ; k++) {
//     //     int cnt = 0;
//     //     for(int i = 0, j = k ; i < SIZE && j >= 0 ; i++, j--) {
//     //         if(board[i][j] == py) cnt++;
//     //         if(board[i][j] != py) {
//     //             if(cnt >= 3) score++; 
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++; 
//     // }
//     // for(int k = 1 ; k < SIZE ; k++) {
//     //     int cnt = 0;
//     //     for(int i = k, j = SIZE - 1 ; i < SIZE && j >= 0 ; i++, j--) {
//     //         if(board[i][j] == py) cnt++;
//     //         if(board[i][j] != py) {
//     //             if(cnt >= 3) score++; 
//     //             cnt = 0;
//     //         }
//     //     }
//     //     if(cnt >= 3) score++;
//     // }
//     for(int k = 0 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = 0, j = k ; i < SIZE && j >= 0 ; i++, j--) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 3, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     for(int k = 1 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = k, j = SIZE - 1 ; i < SIZE && j >= 0 ; i++, j--) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 3, py))ignore = false;
//                 if(cnt >= 2) {
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         } 
//     }
//     cout << "top-right score = " << score << endl;
    
// }




// int stateEvaluate(State *s, int py, bool isplayer) {
//     int score = 0;
    
//     //vertical
//     for(int i = 0 ; i < SIZE ; i++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[j][i] == py && ignore == false) cnt++;
//             if(board[j][i] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(j, i, 1, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(j, i, 1, py)) ignore = false;
//                 if(cnt >= 2) {
//                     if( isplayer == false && cnt >= 3) {
//                         s->Oppo_vertical[0] = j;
//                         s->Oppo_vertical [1] = i;
//                         s->Oppo_vertical[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }    
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
    
//     //horizontal
//     for(int i = 0 ; i < SIZE ; i++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 0, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 0, py)) ignore = false;
//                 if(cnt >= 2) {
//                     if(isplayer == false && cnt >= 3) {
//                         s->Oppo_horizontal[0] = i;
//                         s->Oppo_horizontal [1] = j;
//                         s->Oppo_horizontal[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
    
//     //diagonally(bottom-right)
//     for(int k = 0 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = 0, j = k ; i < SIZE && j < SIZE ; i++, j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 2, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 2, py))ignore = false;
//                 if(cnt >= 2) {
//                     if(isplayer == false && cnt >= 3) {
//                         s->Oppo_bottom_right[0] = i;
//                         s->Oppo_bottom_right [1] = j;
//                         s->Oppo_bottom_right[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     for(int k = 1 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = k, j = 0 ; i < SIZE && j < SIZE ; i++, j++) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 2, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 2, py))ignore = false;
//                 if(cnt >= 2) {
//                     if(isplayer == false && cnt > s->Oppo_bottom_right[2] && cnt >= 3) {
//                         s->Oppo_bottom_right[0] = i;
//                         s->Oppo_bottom_right [1] = j;
//                         s->Oppo_bottom_right[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
    
//     // . . . o
//     // o o o .
//     // . . o .
//     // . . o o
//     //diagonally(top-right)
//     for(int k = 0 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = 0, j = k ; i < SIZE && j >= 0 ; i++, j--) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 3, py))ignore = false;
//                 if(cnt >= 2) {
//                     if(isplayer == false && cnt >= 3) {
//                         s->Oppo_top_right[0] = i;
//                         s->Oppo_top_right [1] = j;
//                         s->Oppo_top_right[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         }  
//     }
//     for(int k = 1 ; k < SIZE ; k++) {
//         int cnt = 0;
//         bool ignore = false;
//         for(int i = k, j = SIZE - 1 ; i < SIZE && j >= 0 ; i++, j--) {
//             if(board[i][j] == py && ignore == false) cnt++;
//             if(board[i][j] != py) {
//                 if(board[j][i] == (3 - py) && isblocked(i, j, 3, py)) ignore = true;
//                 else if(board[j][i] == (3 - py) && !isblocked(i, j, 3, py))ignore = false;
//                 if(cnt >= 2) {
//                     if(isplayer == false && cnt >= 3 && cnt > s->Oppo_top_right[2]) {
//                         s->Oppo_top_right[0] = i;
//                         s->Oppo_top_right [1] = j;
//                         s->Oppo_top_right[2] = cnt;
//                     }
//                     score += pow(cnt, 2); 
//                     score += (cnt - 1);
//                 }  
//                 cnt = 0;
//             }
//         }
//         if(cnt >= 2) {
//             score += pow(cnt, 2); 
//             score += (cnt - 1);
//         } 
//     }
//     return score;
// }


// int getHashFromPosition(int row, int col) {
//     return row * SIZE + col;
// }

// int getRowFromHash(int hash) {
//     return hash / SIZE;
// }

// int getColFromHash(int hash) {
//     return hash % SIZE;
// }

// void getNextMove(State *s, int py, bool isplayer) {
//     for(int i = 0 ; i < SIZE ; i++) {
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[i][j] == py) {
//                 for(int k = 0 ; k < 8 ; k++) {
//                     int nr = i + dir_r[k];
//                     int nc = j + dir_c[k];
//                     int pos = getHashFromPosition(nr, nc);
//                     if(s->discSelectMap.find(pos) == s->discSelectMap.end() && board[nr][nc] == 0 && nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
//                         board[nr][nc] = py;
//                         s->discSelectMap[pos] = new State(stateEvaluate(s, py, isplayer) - stateEvaluate(s, 3 - py, !isplayer));
//                         board[nr][nc] = 0;
//                     }
//                 }
//             }
//         }
//     }
// }

// int defense(State *s, int dir, int cnt) {
//     int x, y;
//     if(dir == 0) {
//         if(board[s->Oppo_horizontal[0]][s->Oppo_horizontal[1]] == 0) { 
//             x = s->Oppo_horizontal[0];
//             y = s->Oppo_horizontal[1];
//             return x * SIZE + y;
//         }
//         else if(board[s->Oppo_horizontal[0]][s->Oppo_horizontal[1]-cnt] == 0) {
//             x = s->Oppo_horizontal[0];
//             y = s->Oppo_horizontal[1]-cnt;
//             return x * SIZE + y;
//         }
//     }
//     if(dir == 1) {
//         if(board[s->Oppo_vertical[0]][s->Oppo_vertical[1]] == 0) {
//             x = s->Oppo_vertical[0];
//             y = s->Oppo_vertical[1];
//             return x * SIZE + y;
//         }
//         else if(board[s->Oppo_vertical[0]-cnt][s->Oppo_vertical[1]] == 0) {
//             x = s->Oppo_vertical[0]-cnt;
//             y = s->Oppo_horizontal[1];
//             return x * SIZE + y;
//         }
//     }
//     if(dir == 2) {
//         if(board[s->Oppo_bottom_right[0]][s->Oppo_bottom_right[1]] == 0) {
//             x = s->Oppo_bottom_right[0];
//             y = s->Oppo_bottom_right[1];
//             return x * SIZE + y;
//         }
//         else if(board[s->Oppo_bottom_right[0]-cnt][s->Oppo_bottom_right[1]-cnt] == 0) {
//             x = s->Oppo_bottom_right[0]-cnt;
//             y = s->Oppo_bottom_right[1]-cnt;
//             return x * SIZE + y;
//         }
//     }
//     if(dir == 3) {
//         if(board[s->Oppo_top_right[0]][s->Oppo_top_right[1]] == 0) {
//             x = s->Oppo_top_right[0];
//             y = s->Oppo_top_right[1];
//             return x * SIZE + y;
//         }
//         else if(board[s->Oppo_top_right[0]-cnt][s->Oppo_top_right[1]+cnt] == 0) {
//             x = s->Oppo_top_right[0]-cnt;
//             y = s->Oppo_top_right[1]+cnt;
//             return x * SIZE + y;
//         }
//     }
//     return 0;
// }

// int alphabeta(State *s, int depth, int alpha, int beta, int py, bool isplayer) {
    
//     getNextMove(s, py, isplayer);
//     if(depth == 0 || s->discSelectMap.size() == 0) return stateEvaluate(s, py, isplayer) - stateEvaluate(s, 3 - py, !isplayer);
    
//     if(isplayer) {
//         s->Score = INT_MIN;
//         for(auto next : s->discSelectMap) {
//             board[getRowFromHash(next.first)][getColFromHash(next.first)] = py;
//             s->Score = max(s->Score, alphabeta(next.second, depth-1, alpha, beta, 3 - py, false));
//             board[getRowFromHash(next.first)][getColFromHash(next.first)] = 0;
//             alpha = max(alpha, s->Score);
            
//             if(alpha >= beta) break;
//         }
//         return s->Score; 
//     }
//     else {
//         s->Score = INT_MAX;
//         for(auto next : s->discSelectMap) {
//             board[getRowFromHash(next.first)][getColFromHash(next.first)] = py;
//             s->Score = min(s->Score, alphabeta(next.second, depth-1, alpha, beta, 3 - py, true));
//             board[getRowFromHash(next.first)][getColFromHash(next.first)] = 0;
//             beta = min(beta, s->Score);

//             if(alpha >= beta) break;
//         }
//         return s->Score; 
//     }
// }

// void write_valid_spot(std::ofstream& fout) {
//     //State *start;
//     int score = 0, py, b = 0, w = 0, x, y;
//     for(int i = 0 ; i < SIZE ; i++) {
//         for(int j = 0 ; j < SIZE ; j++) {
//             if(board[i][j] == 1) b++;
//             if(board[i][j] == 2) w++; 
//         }
//     }
//     if(b == w) py = 1;
//     else if(b > w ) py = 2;
//     if(b == 0 && w == 0 ) {
//         x = SIZE / 2;
//         y = SIZE / 2;
//     }
//     else if(py == 2 && w == 0) {
//         if(board[SIZE / 2][SIZE / 2] == 0) {
//             x = SIZE / 2;
//             y = SIZE / 2;
//         }
//         else {
//             x = SIZE / 2;
//             y = SIZE / 2 + 1;
//         }
//     } 
//     else {
//         State *init = new State(0);
//         State *start = new State(stateEvaluate(init, py, true) - stateEvaluate(init, 3 - py, false));
//         int cntarray[4] = {init->Oppo_horizontal[2], init->Oppo_vertical[2], init->Oppo_bottom_right[2], init->Oppo_top_right[2]};
//         //for(int i = 0 ; i < 4 ; i++) cout << "dir[" << i << "] = " << cntarray[i] << endl;
//         int max = 0, dir = -1;
//         for(int i = 0 ; i < 4 ; i++ ) {
//             if(cntarray[i] > max) {
//                 max = cntarray[i];
//                 dir = i;
//             }
//         }
//         cout << "dir = " << dir << endl;
//         //defense
//         if(dir != -1) {
//             cout << "cntarray[" << dir << "] = " << cntarray[dir] << endl;
//             int hash = defense(init, dir, cntarray[dir] + 1);
//             x = getRowFromHash(hash);
//             y = getColFromHash(hash);
//         }
//         //attack
//         else {
//             score = alphabeta(start, 4, INT_MIN, INT_MAX, py, true);
//             for(auto it : start->discSelectMap) {
//                 if(score == it.second->Score) {
//                     x = getRowFromHash(it.first);
//                     y = getColFromHash(it.first);
//                     break;
//                 }
//             }
//         }
//         if(init->Oppo_horizontal[2] != 0) cout << "Oppo_horizontal has over 3 continuous discs!" << endl;
//         if(init->Oppo_vertical[2] != 0) cout << "Oppo_vertical has over 3 continuous discs!" << endl;
//         if(init->Oppo_bottom_right[2] != 0) cout << "Oppo_bottom_right has over 3 continuous discs!" << endl;
//         if(init->Oppo_top_right[2] != 0) cout << "Oppo_top_right has over 3 continuous discs!" << endl;
//     }
//     cout << "player = " << py << endl;
//     stateEvaluate_check(py);
//     stateEvaluate_check(3-py);
//     cout << "score = " << score << endl;
//     fout << x << " " << y << std::endl;
//     //cout << x << " " << y << std::endl;
//     // Remember to flush the output to ensure the last action is written to file.
//     fout.flush();
// }

// int main(int, char** argv) {
//     std::ifstream fin(argv[1]);
//     std::ofstream fout(argv[2]);
//     read_board(fin);
//     write_valid_spot(fout);
//     fin.close();
//     fout.close();
//     return 0;
// }

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
    board[row][col] = py;
    int cont[8] = {0};
    bool retval = false;
    for (int k = 0; k < 8; k++) {
        for (int i = 1; i < len; i++) {
            int nr = dir_r[k]*i + row, nc = dir_c[k]*i + col; 
            if(board[nr][nc] != py) break;
            if (inBoundary(nr, nc) && board[nr][nc] == py) cont[k]++; 
        }
    }
    for (int k = 0; k < 4; k++) {
        if (cont[k] + cont[7-k] + 1 >= len) retval = true;
    }
    board[row][col] = EMPTY;
    return retval;
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
                if (cont == len) num_lines++;
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
                if (cont == len) num_lines++;
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
    for(int i = 2 ; i <= 5 ; i++) {
        score += numberOfLines(i, py) * (pow(i, 2) + (i - 1));
    } 
    return score;
}

void stateEvaluate_check( int py) {
    
    for(int i = 2 ; i <= 5 ; i++) {
        int score = 0;
        score = numberOfLines(i, py) * (pow(i, 2) + (i - 1));
        cout << i << "continuous discs * " << numberOfLines(i, py) << " = " << score << endl;
    } 
    
}
//find the beneficial directions
void getNextMove(State *s, int py) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] != py) continue;
            for(int k = 0 ; k < 8 ; k++) {
                int nr = i + dir_r[k];
                int nc = j + dir_c[k];
                int pos = getHashFromPosition(nr, nc);
                if(s->discSelectMap.find(pos) == s->discSelectMap.end() && inBoundary(nr, nc) && board[nr][nc] == EMPTY) {
                    
                    s->discSelectMap[pos] = new State(0);
    
                }
            }
        }
    }
}

int defense(int py) {
    int pos = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY && formALine(i, j, 4, py)) 
                pos = getHashFromPosition(i, j);
        }
    }
    return pos;
}

int alphabeta(State *s, int depth, int alpha, int beta, int py, bool isplayer) {
    
    getNextMove(s, py);
    if(depth == 0 || s->discSelectMap.size() == 0) return stateEvaluate(py)*2 - stateEvaluate(3 - py);
    
    if(isplayer) {
        s->Score = INT_MIN;
        for(auto &next : s->discSelectMap) {
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = py;
            s->Score = max(s->Score, alphabeta(next.second, depth-1, alpha, beta, 3 - py, false));
            board[getRowFromHash(next.first)][getColFromHash(next.first)] = 0;
            alpha = max(alpha, s->Score);
            if(alpha >= beta) break;
        }
        return s->Score; 
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
        return s->Score; 
    }
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
        int pos = defense(3-player);
        if (pos >= 0) {
            x = getRowFromHash(pos);
            y = getColFromHash(pos);
            cout << "defense!\n";
        } else {
            cout << "attack!\n";
            State *start = new State(0);
            alphabeta(start, 4, INT_MIN, INT_MAX, player, true);            
            for(auto &it : start->discSelectMap) {
                if(it.second->Score >= max_score) {
                    max_pos = it.first;
                    max_score = it.second->Score;
                }
                cout << "discSelectMap : " << getRowFromHash(it.first) << " " << getColFromHash(it.first) << endl; 
            }
            x = getRowFromHash(max_pos);
            y = getColFromHash(max_pos);
        }
    }
    cout << x << " " << y << " " << max_score << std::endl;
    stateEvaluate_check(player);
    stateEvaluate_check(3 - player);
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