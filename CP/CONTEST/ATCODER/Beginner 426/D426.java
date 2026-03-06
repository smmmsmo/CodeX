import java.util.Scanner;

public class D426 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            sc.nextInt();
            String s = sc.next();

            int ops0 = solve(s, '0');
            int ops1 = solve(s, '1');

            System.out.println(Math.min(ops0, ops1));
        }
        sc.close();
    }

    static int solve(String s, char target) {
        int n = s.length();
        int ops = 0;
        int left = 0, right = n - 1;

        while (left <= right) {
            if (s.charAt(left) == target) {
                left++;
            } else if (s.charAt(right) == target) {
                right--;
            } else {
                ops++;
                left++;
            }
        }

        return ops;
    }
}
