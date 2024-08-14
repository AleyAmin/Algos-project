#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

const int BOARD_WIDTH = 4;
const int BOARD_HEIGHT = 3;

vector<pair<int, int>> initial_white_positions = { {3, 0}, {3, 1}, {3, 2} };
vector<pair<int, int>> initial_black_positions = { {0, 0}, {0, 1}, {0, 2} };

vector<pair<int, int>> knight_moves = { {2, 1}, {1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1} };

bool is_valid_position(pair<int, int> position) {
    return position.first >= 0 && position.first < BOARD_WIDTH &&
        position.second >= 0 && position.second < BOARD_HEIGHT;
}

vector<pair<int, int>> generate_moves(pair<int, int> start_position) {
    vector<pair<int, int>> moves;
    for (size_t i = 0; i < knight_moves.size(); ++i) {
        pair<int, int> new_position = { start_position.first + knight_moves[i].first, start_position.second + knight_moves[i].second };
        if (is_valid_position(new_position)) {
            moves.push_back(new_position);
        }
    }
    return moves;
}

bool is_goal_state(const vector<pair<int, int>>& white_positions, const vector<pair<int, int>>& black_positions) {
    set<pair<int, int>> white_goal = { {0, 0}, {0, 1}, {0, 2} };
    set<pair<int, int>> black_goal = { {3, 0}, {3, 1}, {3, 2} };
    return set<pair<int, int>>(white_positions.begin(), white_positions.end()) == white_goal &&
        set<pair<int, int>>(black_positions.begin(), black_positions.end()) == black_goal;
}

struct State {
    vector<pair<int, int>> white_positions;
    vector<pair<int, int>> black_positions;
    int moves;
    vector<tuple<char, pair<int, int>, pair<int, int>>> path;
};

pair<int, vector<tuple<char, pair<int, int>, pair<int, int>>>> min_moves(
    const vector<pair<int, int>>& initial_white_positions, const vector<pair<int, int>>& initial_black_positions) {

    queue<State> q;
    set<pair<vector<pair<int, int>>, vector<pair<int, int>>>> visited;
    q.push({ initial_white_positions, initial_black_positions, 0, {} });

    while (!q.empty()) {
        State current_state = q.front();
        q.pop();

        if (is_goal_state(current_state.white_positions, current_state.black_positions)) {
            return { current_state.moves, current_state.path };
        }

        vector<pair<int, int>> positions[2] = { current_state.white_positions, current_state.black_positions };
        char colors[2] = { 'W', 'B' };

        for (int k = 0; k < 2; ++k) {
            for (size_t i = 0; i < positions[k].size(); ++i) {
                vector<pair<int, int>> possible_moves = generate_moves(positions[k][i]);
                for (size_t j = 0; j < possible_moves.size(); ++j) {
                    pair<int, int> new_pos = possible_moves[j];
                    if (find(positions[0].begin(), positions[0].end(), new_pos) == positions[0].end() &&
                        find(positions[1].begin(), positions[1].end(), new_pos) == positions[1].end()) {

                        vector<pair<int, int>> new_positions = positions[k];
                        new_positions[i] = new_pos;
                        pair<vector<pair<int, int>>, vector<pair<int, int>>> new_state_key =
                            k == 0 ? make_pair(new_positions, current_state.black_positions) : make_pair(current_state.white_positions, new_positions);

                        if (visited.find(new_state_key) == visited.end()) {
                            visited.insert(new_state_key);
                            vector<tuple<char, pair<int, int>, pair<int, int>>> new_path = current_state.path;
                            new_path.push_back(make_tuple(colors[k], positions[k][i], new_pos));
                            q.push({ new_state_key.first, new_state_key.second, current_state.moves + 1, new_path });
                        }
                    }
                }
            }
        }
    }
    return { -1, {} }; 
}

int main() {
    pair<int, vector<tuple<char, pair<int, int>, pair<int, int>>>> result = min_moves(initial_white_positions, initial_black_positions);
    int min_moves = result.first;
    vector<tuple<char, pair<int, int>, pair<int, int>>> path = result.second;
    cout << "The minimum number of moves required is: " << min_moves << endl;
    if (min_moves != -1) {
        cout << "The moves are:" << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "Move " << get<0>(path[i]) << " knight from (" << get<1>(path[i]).first << "," << get<1>(path[i]).second << ") to (" << get<2>(path[i]).first << "," << get<2>(path[i]).second << ")" << endl;
        }
    }
    return 0;
}
