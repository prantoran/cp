#include<bits/stdc++.h>
using namespace std;

const int mxn = 111;

int t,ca,n,m,ans,p,px[11111],py[11111],a[111][111],w,wx[11111],wy[11111];

int lineid;

vector< pair<int,int> > lines[11111];
pair<int,int> linesize[11111];

int cover[111][111];

bool cmp(const pair<int,int> &aa,const pair<int,int> &bb){
    return aa.first<bb.first;
}

int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d",&t);

    for(ca=1;ca<=t;ca++){
        memset(a,0,sizeof(a));

        scanf("%d %d",&n,&m);

        scanf("%d",&p);
        for(int i = 0; i < p ;i++){
            scanf("%d %d",&px[i],&py[i]);
            px[i]--;
            py[i]--;
            a[px[i]][py[i]]=1;
        }

        scanf("%d",&w);
        for(int i = 0 ; i<w;i++){
            scanf("%d %d",&wx[i],&wy[i]);
            wx[i]--;
            wy[i]--;
            a[wx[i]][wy[i]]=2;
        }

        for(int i = 0 ; i < 11111;i++){
            lines[i].clear();
        }
        memset(cover,0,sizeof(cover));
        lineid=0;
        int cnt = 0;

        for(int i = 0 ; i < n;i++){

            for(int j = 0 ; j<m;j++){
                if(a[i][j]==2){
                    if(cnt){
                        lineid++;
                        cnt =0;
                    }
                }
                else if(a[i][j]==1){
                    cnt++;
                    lines[lineid].push_back(make_pair(i,j));
                    cover[i][j]++;
                }
            }
            lineid++;
        }

        cnt=0;
        for(int j = 0 ; j < n;j++){
            for(int i = 0 ; i < m;i++){
                if(a[i][j]==2){
                    if(cnt){
                        lineid++;
                        cnt =0;
                    }
                }
                else if(a[i][j]==1){
                    cnt++;
                    lines[lineid].push_back(make_pair(i,j));
                    cover[i][j]++;
                }
            }
            lineid++;
        }
        for(int i = 0 ; i < lineid;i++){
            linesize[i]=make_pair(lines[i].size(),i);
        }
        sort(linesize,linesize+lineid,cmp);
        ans =0;

        for(int i = 0 ; i < lineid;i++){
            int id = linesize[i].second;

            for(int xx,yy,j = 0 , len = lines[id].size();j<len;j++){
                xx=lines[id][j].first;
                yy=lines[id][j].second;
                if(cover[xx][yy]==1){
                    for(int k = 0,xxx,yyy ; k<j;k++){
                        xxx=lines[id][k].first;
                        yyy=lines[id][k].second;
                        cover[xxx][yyy]++;
                    }
                    ans++;
                    break;
                }
                else if(cover[xx][yy]>0){
                    cover[xx][yy]--;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
