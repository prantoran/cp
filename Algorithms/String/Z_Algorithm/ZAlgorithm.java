import java.util.Vector;

/**
 * Created by pinku on 2/19/17.
 */
public class ZAlgorithm {
    /*
		Steps:
			1. Take input pattern P and searched string T
			2. Set ZSIZE, TSIZE
			3. Clear Z array
		Notes:
			The strings P and T are 0-based
			The Z array is 1-based
	*/
    private static final int ZMAX = 211111;
    private static final int Z_UNASSIGNED = -1;

    public String P,T;
    int[] Z = new int[ZMAX+7];
    public int ZSIZE,PSIZE;

    ZAlgorithm(){

    }
    ZAlgorithm(String PP,String TT){
        this.P = PP;
        this.T = TT;
    }

    public void clearZArray(){
        for(int i = 0 ; i <=ZMAX;i++){
            Z[i]=Z_UNASSIGNED;
        }
    }

    public void preprocessZArray(){
        ZSIZE = P.length();
        Z[0]=Z[1]=0; //Z[1] is 0 by default, because we cannot consider whole string
        int L=0,R=0; //for kth iteration L and R points to l(k-1) and r(k-1) of previous iteration
        int beta;
        int k = 1, id,k2;
        while(k<ZSIZE && P.charAt(k-1)==P.charAt(k)){ // calculating Z[2]
            k++;
        }
        L=2;
        R=k;
        Z[2]=R-L+1;
        for(k=3;k<=ZSIZE;k++){
            if(k<=R){
                k2 = k - L + 1;
                beta = R - k + 1;

                if(Z[k2]<beta){
                    Z[k]=Z[k2];
                }
                else if(Z[k2]>beta){
                    Z[k]=beta;
                }
                else{ //Z[k2] == beta
                    id = beta;
                    while(R<ZSIZE && P.charAt(R) == P.charAt(id)){
                        R ++;
                        id ++;
                    }
                    L = k;
                    Z[k] = R - L + 1;
                }
            }
            else{
                id = k-1;
                k2 = 0;
                while(id<ZSIZE && P.charAt(k2) == P.charAt(id)){
                    id ++;
                    k2 ++;
                }
                L = k;
                R = id;
                Z[k] = R-L+1;

            }
        }
    }
    Vector<Integer> findExactMatches(){
        PSIZE = P.length();
        P += "$";
        P += T;
        ZSIZE = P.length();
        preprocessZArray();
        Vector<Integer> ret = new Vector<Integer>();
        for(int i = 1;i<=ZSIZE;i++){
            if(Z[i]==PSIZE){
                ret.add(i-PSIZE-1);
            }
        }
        return ret;
    }
}

