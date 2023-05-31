public class seguida { 
    public static void main(String[] args) { 
        int n=1;
        String text;
        if (args.length==1) 
            n= Integer.parseInt(args[0]);
        for (int i = 1; i <= n; i++) { 
            text = i + "\n";
            System.out.printf(text); 
        }
    } 
}
