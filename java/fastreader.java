
class FastReader {
    private BufferedReader br;
    private StringTokenizer st;

    FastReader()  {
        br = new BufferedReader(new InputStreamReader(System.in));
    }

    private String next() {
        while (st == null || !st.hasMoreElements())  {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    int nextInt()  {
        return Integer.parseInt(next());
    }
}

// FastReader in = new FastReader();
// int n = in.nextInt();