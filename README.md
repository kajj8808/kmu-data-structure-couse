# Sorting Practice (Quick Sort)

### 결과 분석

- 이전의 동일한 방식(분할 정복)으로 진행되는 merge sort 와 비교해 보았을때 merge sort 의 경우 20번 출력 하였을때 값을 이동한 횟수(88)는 merge 의 경우가 많고 (qucik의 경우 22), 이동 횟수는 quick sort가 더 나오는 결과를 보이고 있습니다(merge : 50 , quick, 84). 이 결과를 보았을때 실제로 값이 많은 경우나 값의 이동이 많은 경우에는 값을 실제로 이동하는 횟수가 적은 quick sort가 더 유리 할것으로 보이고, 값이 적을 경우에는 이동 횟수가 적은 merge가 더 효과적으로 보입니다.
- shell 의 경우에도 merge 와 비슷한 비교횟수, 이동횟수를 가진것으로 보아 동일하게 적용될 것이라 보입니다.
- selection 의 경우 두 부분 다 좋은 결과를 보입니다 하지만 selection 의 특성상 값이 많아지면 이동횟수도 같이 많이 늘어나는 경우를 보일것으로 예상이됩니다.
- insertion 의 경우 에는 많은 이동 횟수가 나오는 결과를 보입니다. 값이 많아 질수록 + 더 값이 정렬이 되어있지 않는 경우 더 많은 이동횟수가 생길것으로 예상됩니다.
- bubble 의 경우 에는 이동횟수 비교횟수가 많은 결과를 보입니다(값이 정렬되어 있지 않아 이런 경우가 일어난것으로 보입니다.). bubble의 특성상 값이 일정하게 정렬할경우가 많아질 경우 더 비교횟수가 많이 날것으로 예상됩니다.

### 결과 화면

- #### 재귀방식 ![](https://github.com/kajj8808/kmu-data-structure-couse/assets/71279997/4f2c6895-c8ca-4865-8c72-5ed7be6e0b90)
- #### 반복방식 ![](https://github.com/kajj8808/kmu-data-structure-couse/assets/71279997/d20ceb22-055a-4bad-b096-054fcce0d5a8)

