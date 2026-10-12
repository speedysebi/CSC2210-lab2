/** Sebastien Huelke, SPA 2.1 - made it better
 * just basic improvements
 * const is the only thing that one needs
 * i used the "class right one"
 * even though it shouldnt be used in prod code
 *  **/
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

constexpr int MIN_VALUE = 0;
constexpr int MAX_VALUE = 100;
constexpr int CAPACITY = MAX_VALUE - MIN_VALUE + 1;

constexpr int LABEL_WIDTH = 3;
constexpr int TICK_SPACING = 5;
constexpr int MIN_AXIS = 10;

/** does the thing **/
int toIndex(int value) {
    return value - MIN_VALUE;
}

/** array stuff **/
void clearCounts(int counts[]) {
    for (int i = 0; i < CAPACITY; i++) {
        counts[i] = 0;
    }
}

/** handles it **/
void skipBadToken() {
    cin.clear();
    string bad;
    cin >> bad;
    cout << "Error: \"" << bad << "\" is not a whole number, skipped" << endl;
}

/** skips **/
void skipRestOfLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/** bounds **/
bool readBounds(int &lower, int &upper) {
    while (true) {
        cout << "Enter lower and upper bounds (" << MIN_VALUE << " to "
             << MAX_VALUE << "): ";
        if (!(cin >> lower)) {
            if (cin.eof()) {
                return false;
            }
            skipBadToken();
            skipRestOfLine();
            continue;
        }
        if (!(cin >> upper)) {
            if (cin.eof()) {
                return false;
            }
            skipBadToken();
            skipRestOfLine();
            continue;
        }
        if (lower < MIN_VALUE || lower > MAX_VALUE ||
            upper < MIN_VALUE || upper > MAX_VALUE) {
            cout << "Error: bounds must be between " << MIN_VALUE << " and "
                 << MAX_VALUE << ", try again" << endl;
            skipRestOfLine();
        } else if (lower > upper) {
            cout << "Error: lower bound " << lower
                 << " is greater than upper bound " << upper
                 << ", try again" << endl;
            skipRestOfLine();
        } else {
            return true;
        }
    }
}

/** reads **/
void readData(int counts[], int lower, int upper, int &accepted, int &rejected) {
    accepted = 0;
    rejected = 0;
    int value;
    while (true) {
        if (cin >> value) {
            if (value < lower || value > upper) {
                cout << "Error: value " << value << " is out of range" << endl;
                rejected++;
            } else {
                counts[toIndex(value)]++;
                accepted++;
            }
        } else if (cin.eof()) {
            return;
        } else {
            skipBadToken();
            rejected++;
        }
    }
}

/** finds it **/
int mostFrequent(const int counts[], int lower, int upper) {
    int best = lower;
    for (int value = lower + 1; value <= upper; value++) {
        if (counts[toIndex(value)] > counts[toIndex(best)]) {
            best = value;
        }
    }
    return best;
}

/** row **/
int longestRow(const int counts[], int lower, int upper) {
    return counts[toIndex(mostFrequent(counts, lower, upper))];
}

/** width **/
int axisWidth(int longest) {
    int width = MIN_AXIS;
    while (width < longest) {
        width += MIN_AXIS;
    }
    return width;
}

/** draws **/
void drawRow(int value, int count) {
    cout << setw(LABEL_WIDTH) << value << " |";
    for (int i = 0; i < count; i++) {
        cout << '#';
    }
    cout << endl;
}

/** draws more **/
void drawRows(const int counts[], int lower, int upper) {
    for (int value = upper; value >= lower; value--) {
        drawRow(value, counts[toIndex(value)]);
    }
}

/** axis **/
void drawHorizontalAxis(int width) {
    cout << setw(LABEL_WIDTH) << "" << " +";
    for (int i = 1; i <= width; i++) {
        if (i % TICK_SPACING == 0) {
            cout << '+';
        } else {
            cout << '-';
        }
    }
    cout << endl;
}

/** labels **/
void labelHorizontalAxis(int width) {
    cout << setw(LABEL_WIDTH) << "" << " ";
    for (int i = 0; i < width; i += TICK_SPACING) {
        cout << left << setw(TICK_SPACING) << i << right;
    }
    cout << width << endl;
}

/** prints stuff **/
void printSummary(const int counts[], int lower, int upper, int accepted, int rejected) {
    cout << endl;
    cout << "Values counted:  " << accepted << endl;
    cout << "Values rejected: " << rejected << endl;
    if (accepted == 0) {
        cout << "Most frequent:   none (no values were counted)" << endl;
    } else {
        int best = mostFrequent(counts, lower, upper);
        cout << "Most frequent:   " << best << " (" << counts[toIndex(best)]
             << (counts[toIndex(best)] == 1 ? " time)" : " times)") << endl;
    }
}

/** main **/
int main() {
    int counts[CAPACITY];
    clearCounts(counts);

    int lower;
    int upper;
    if (!readBounds(lower, upper)) {
        cout << endl << "Error: no valid bounds were entered" << endl;
        return 1;
    }

    cout << "Enter values from " << lower << " to " << upper
         << " (Ctrl+Z then Enter on Windows, Ctrl+D on Mac/Linux to finish):"
         << endl;
    int accepted;
    int rejected;
    readData(counts, lower, upper, accepted, rejected);

    cout << endl;
    drawRows(counts, lower, upper);
    int width = axisWidth(longestRow(counts, lower, upper));
    drawHorizontalAxis(width);
    labelHorizontalAxis(width);
    printSummary(counts, lower, upper, accepted, rejected);
    return 0;
}
