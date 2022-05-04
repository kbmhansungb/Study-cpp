#pragma once

/*
	이진 탐색 Binary search

	1, 2, 3, ... , 7, 8, 9, 10

	find 6
	L 1, R 10, M 5 // 6 > M 이므로 L 변경
	L 5, R 10, M 7 // M > 7 이므로 R 변경
	L 5, R 7, M 6 // M == 이므로 종료.
*/