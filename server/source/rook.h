for (size_t k = i + 1; k < 8; ++k) {
if (bd[k][j] == Empty) {
mov[2] = k;
mov[3] = j;
avail_moves.push_back(mov);
} else {
if (bd[k][j] != temp) {
mov[2] = k;
mov[3] = j;
avail_moves.push_back(mov);
}
break;
}

}

for (size_t k = i - 1; k < 8; --k) {
if (bd[k][j] == Empty) {
mov[2] = k;
mov[3] = j;
avail_moves.push_back(mov);
} else {
if (bd[k][j] != temp) {
mov[2] = k;
mov[3] = j;
avail_moves.push_back(mov);
}
break;
}
}



for (size_t k = j + 1; k < 8; ++k) {
if (bd[i][k] == Empty) {
mov[2] = i;
mov[3] = k;
avail_moves.push_back(mov);
} else {
if (bd[i][k] != temp) {
mov[2] = i;
mov[3] = k;
avail_moves.push_back(mov);
}
break;
}

}

for (size_t k = j - 1; k < 8; --k) {
if (bd[i][k] == Empty) {
mov[2] = i;
mov[3] = k;
avail_moves.push_back(mov);
} else {
if (bd[i][k] != temp) {
mov[2] = i;
mov[3] = k;
avail_moves.push_back(mov);
}
break;
}

}