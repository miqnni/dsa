class Node {
    int data;
    Node next;

    Node(int d){
        data=d;
        next=null;
   }
}

class Solution {
    private void printList(Node head, boolean headIsGuard) {
        if (head == null) {
            System.out.println("(/)");
            return;
        }
        
        Node currNode = head;
        if (headIsGuard) {
            System.out.print("G -> ");
            currNode = currNode.next;
        }
        
        while (currNode != null) {
            System.out.printf("%d -> ", currNode.data);
            currNode = currNode.next;
        }
        System.out.println("(/)");
    }
    
    private int listLength(Node head) {
        if (head.next == null)
            return 0;
        
        Node currNode = head;
        int nodeCount = 0;
        while (currNode != null) {
            nodeCount++;
            currNode = currNode.next;
        }
        
        return nodeCount;        
    }
    
    public Node rotateERROR(Node head, int k) { // TODO: find and fix the infinite loop
        if (k == 0)
            return head;
        
        int l = listLength(head);
        if (l < 2 || k == l)
            return head;
        
        int betterK = k % l;
        int nodeCount = 0;
        
        Node guard = new Node(-1);
        guard.next = head;
        
        Node prevGuardNext = guard.next; // The next node after the GUARD before the rotation
        Node currNode = guard.next;
        while (currNode != null) {
            nodeCount++;
            // System.out.printf("%d | ", currNode.data);
            // printList(head, false);
            
            if (nodeCount == betterK) {
                if (currNode.next == null) {
                    break;
                }
                
                // We are on the node whose next node should be guard.next
                // after the rotation.
                guard.next = currNode.next; // The next node will be the first node of the rotated list.
                currNode.next = null; // This will be the last node of the rotated list.
                currNode = guard.next; // Go to the node that would be next before the rotation-related changes.
                
                // We know that we weren't at the last node (if k == l), so we can safely continue. Otherwise, there would be a risk of an infinite loop
                continue; // Prevent execution of `currNode = currNode.next;` because `currNode.next` is now NULL.
            }
            
            if (currNode.next == null) {
                // We are on the node that was the last one before the rotation.
                currNode.next = prevGuardNext; // Reconnect the end of the rotated list with the original head.
                break; // currNode.next is now not NULL, but we have traversed the list and made all changes. Let's stop the loop here to prevent infinite execution.
            }
            
            currNode = currNode.next;
        }
        head = guard.next;
        return head; // TODO
    }
    
    public Node rotate(Node head, int k) {
        if (head == null || head.next == null || k == 0)
            return head;
                
        // Step 1: Calculate list length, SAVE THE TAIL and reduce k if it exceeds length
        int l = 1;
        Node tail = head;
        while (tail.next != null) {
            tail = tail.next;
            l++;
        }
        k = k % l;
        
        if (k == 0)
            return head;
        
        // Step 2: Find the new list tail (after k elements)
        // and the new list head (the element after the new tail)
        Node newTail = head;
        for (int i = 1; i < k; i++) {
            newTail = newTail.next;
        }
        
        Node newHead = newTail.next;
        
        // Step 3: Cut the list after newTail and connect the previous 
        newTail.next = null;
        tail.next = head;
        
        return newHead;
    }
}

