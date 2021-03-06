#pragma once


/*

    탐욕법(greedy)

    탐욕법 알고리즘이란 현재 상황에서 가장 좋은 것을 고르는 알고리즘을 말함
    그리디 알고리즘은 동적 프로그래밍을 간단한 문제 해결에 사용하면 지나치게 많은 일을
    한다는 것에 착안하여 고안.

    Greedy알고리즘은 현재 상황에서 가장 좋은 결과를 선택해 나가는 방식.
    하지만 이 가장 좋은 결과는 최종적인 결과 도출에 대한 최적해를 보장해 주는 것이 아님.

    Greedy알고리즘의 조건

    탐욕적인 선택은 항상 안전하다는 것이 보장되어야 한다.
    여기서 안전하다라는 것은 이 선택으로 전체 문제의 최적해를 반드시 도출 할 수 있어야 한다.
    1. 그리디 알고리즘이 항상 최적해를 구하지 않기때문에 최적해 구하는 문제에서는 위의 조건이 보장되어야 한다.

    최적 부분 구조 조건
    문제에 대한 최종 해결 방법이 부분 문제에 대해서도 또한 최적의 해결 방법이다라는 조건
    이 말은 전체 문제의 안에는 여러 단계가 존재하고, 이 여러 단계 내의 하나 하나의 단계에 대해 최적해가
    도출되어야 한다는 것.

    https://velog.io/@contea95/%ED%83%90%EC%9A%95%EB%B2%95%EA%B7%B8%EB%A6%AC%EB%94%94-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98

    DP를 조금 단순하게 구하고자 하는 건가...

    ------------------------------------------------------------------------------------------

    https://programmers.co.kr/learn/courses/30/lessons/42862
    체육복 문제가 그리디 였구나,,
    그건 그렇지.. 답이 하나닌까,,
    새로푼거 어디갔냐,, ㅂㄷㅂㄷ.. 전에 개같이 풀어놓은거만 있네,,

    조이스틱으로 이름만들기
    https://programmers.co.kr/learn/courses/30/lessons/42860
    inline을 사용했는데
    https://boycoding.tistory.com/220
    보고 외우도록 하자.

*/