import java.util.Scanner;

public class B426 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        
        int[] count = new int[26];
        
        for(int i = 0; i < s.length(); i++) {
            count[s.charAt(i) - 'a']++;
        }
        
        for(int i = 0; i < 26; i++) {
            if(count[i] == 1) {
                System.out.println((char)('a' + i));
                break;
            }
        }
        
        sc.close();
    }
}