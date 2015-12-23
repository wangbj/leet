public class Solution {
    private class Pair {
        ListNode first;
        ListNode second;
        
        Pair(ListNode l, ListNode r) {
            first = l;
            second = r;
        }
    }
    public int listSize(ListNode head) {
        if (head == null) return 0;
        ListNode p = head;
        int size = 0;
        
        while (p != null) {
            ++size;
            p = p.next;
        }
        return size;
    }
    
    public Pair splitAt(ListNode head, int k) {
        if (head == null) return new Pair(null, null);
        if (k == 0) return new Pair(null, head);

        ListNode left = null;
        ListNode right = null;
        
        ListNode p = null;
        ListNode q = head;
        
        while(k-- > 0 && q != null) {
            if (p == null) {
                p = new ListNode (q.val);
                left = p;
            } else {
                p.next = new ListNode(q.val);
                p = p.next;
            }
            q = q.next;
        }
        p = null;
        while(q != null) {
            if (p == null) {
                p = new ListNode(q.val);
                right = p;
            } else {
                p.next = new ListNode(q.val);
                p = p.next;
            }
            q = q.next;
        }
        return new Pair(left, right);
    }
    public ListNode concat(ListNode left, ListNode right) {
        if (left == null) return right;
        if (right == null) return left;
        
        ListNode p = left;
        
        while(p.next != null) {
            p = p.next;
        }
        
        p.next = right;
        
        return left;
    }
    public ListNode rotateRight(ListNode head, int k) {
        if (head == null) return null;
        int size = listSize(head);
        if (k >= size) k = k % size;
        if (k == 0) return head;
        Pair p = splitAt(head, size-k);
        return concat(p.second, p.first);
    }
}
