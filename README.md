# Red-Black Tree 구현

Balanced search tree로 많이 쓰이는 Red-black tree (이하 RB tree)를 C 언어로 구현하는 과제입니다.
구현하는 추상 자료형 (ADT: abstract data type)은 ordered set, multiset 입니다.

## 구현 범위
다음 기능들을 수행할 수 있도록 RB tree를 구현합니다.

- tree = `new_tree()`: RB tree 구조체 생성
  - 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
- `delete_tree(tree)`: RB tree 구조체가 차지했던 메모리 반환
  - 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)

- `tree_insert(tree, key)`: key 추가
  - 구현하는 ADT가 multiset이므로 이미 같은 key의 값이 존재해도 하나 더 추가 합니다.
- ptr = `tree_find(tree, key)`
  - RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
  - 해당하는 node가 없으면 NULL 반환
- `tree_erase(tree, ptr)`: RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
- ptr = `tree_min(tree)`: RB tree 중 최소 값을 가진 node pointer 반환
- ptr = `tree_max(tree)`: 최대값을 가진 node pointer 반환

- `tree_to_array(tree, array, n)`
  - RB tree의 내용을 *key 순서대로* 주어진 array로 변환
  - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
  - array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.

## 구현 규칙
- `src/rbtree.c` 이외에는 수정하지 않고 test를 통과해야 합니다.
- `make test`를 수행하여 `Passed All tests!`라는 메시지가 나오면 모든 test를 통과한 것입니다.
- Sentinel node를 사용하여 구현했다면 `test/Makefile`에서 `CFLAGS` 변수에 `-DSENTINEL`이 추가되도록 comment를 제거해 줍니다.

## 과제의 의도 (Motivation)

- 복잡한 자료구조(data structure)를 구현해 봄으로써 자신감 상승
- C 언어, 특히 포인터(pointer)와 malloc, free 등의 system call에 익숙해짐.
- 동적 메모리 할당(dynamic memory allocation)을 직접 사용해 봄으로써 동적 메모리 할당의 필요성 체감 및 data segment에 대한 이해도 상승
- 고급 언어에서 기본으로 제공되는 자료구조가 세부적으로는 어떻게 구현되어 있는지 경험함으로써 고급 언어 사용시에도 효율성 고려

## 참고문헌
- [위키백과: 레드-블랙 트리](https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC)
([영어](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree))
- CLRS book (Introduction to Algorithms) 13장 레드 블랙 트리 - Sentinel node를 사용한 구현
- [Wikipedia:균형 이진 트리의 구현 방법들](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree#Implementations)


## 개인 정리
### 특성

- 특성 1. 노드는 레드 or 블랙 중 하나이다
- 특성 2. 루트 노드는 블랙이다
- 특성 3. 모든 리프 노드들은 블랙이다
- 특성 4. 레드 노드의 자식노드 양쪽은 언제나 모두 블랙이다 -> 레드 노드는 연속된 위치에 존재할 수 없다
- 특성 5. 어떤 노드로부터 그에 속한 하위 리프 노드에 도달하는 모든 경로는, 같은 블랙 높이를 가진다

### 동작
- O(log n)의 색변환과
- 최대 3회의 트리 회전(삽입은 2회)이 필요하다 -> 여전히 O(log n)의 연산이 수행됨

### 삽입
- 삽입 노드는 붉은색이다
- uncle node 개념을 도입한다. 옆노드의 부모 노드를 unclde node라고 지칭한다
- z.p가 루트면 z.p는 블랙이다

이때, 새로운 특성이 추가 된다

- 특성 3은 언제나 변하지 않는다 (모든 리프 노드들은 검은색)
- 특성 4는 적색 노드의 추가, 검은색 노드의 적색 노드로의 전환, 회전에 의해서 제대로 지켜지지 않는다 (적색 노드의 모든 자식은 검은색이다)
- 특성 5는 검은색 노드의 추가, 적색 노드 -> 검은색 노드로의 전환, 회전에 의해서 제대로 지켜지지 않는다 (어떤 노드로부터 시작되어 리프 노드에 도달하는 모든 경로에는 모두 같은 개수의 블랙 노드가 존재)

- 삽입 원소 N
- N의 부모 P
- P의 부모 G
- N의 삼촌 U


### 초기화
- z는 추가되는 레드 노드다
- z.p가 루트이면, z.p의 색은 처음 black이다

### 삽입 case1
- N이라는 새로운 노드가 트리의 시작에 위치
- 첫번째 속성(트리 시작은 검은색)을 만족하기 위해 N을 검은색으로 표현함
- 아니면 case2로 이동

### 삽입 case2
- 부모 노드 P가 검은색이라면, 네 번째 속성이 유효하다. 
- 아니면 case3으로 이동

### 삽입 case3
- P & U 모두 붉은색 노드라면, 다섯 번째 속성을 만족하기 위해서
- P & U를 모두 검은색으로 바꾸고, G를 붉은색으로 바꾼다.
- P는 왼쪽 자식일 때와 오른쪽 자식일 때가 다르다

