struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionMine {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int carry = 0;
    ListNode *dummyHead = new ListNode(0);
    ListNode *tail = dummyHead;
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
      int tmp = carry;
      if (l1 != nullptr) {
        tmp += l1->val;
        l1 = l1->next;
      }
      if (l2 != nullptr) {
        tmp += l2->val;
        l2 = l2->next;
      }
      ListNode *newNode = new ListNode(tmp % 10);
      carry = tmp / 10;
      tail->next = newNode;
      tail = newNode;
    }
    ListNode *result = dummyHead->next;
    delete dummyHead;
    return result;
  }
};

class SolutionRecursive {
public:
  ListNode *add(ListNode *l1, ListNode *l2, int carry) {
    if (!l1 && !l2 && carry == 0) {
      return nullptr;
    }

    int v1 = 0;
    int v2 = 0;
    if (l1) {
      v1 = l1->val;
    }
    if (l2) {
      v2 = l2->val;
    }

    int sum = v1 + v2 + carry;
    int newCarry = sum / 10;
    int nodeValue = sum % 10;

    ListNode *nextNode =
        add((l1 ? l1->next : nullptr), (l2 ? l2->next : nullptr), newCarry);

    return new ListNode(nodeValue, nextNode);
  }

  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) { return add(l1, l2, 0); }
};
