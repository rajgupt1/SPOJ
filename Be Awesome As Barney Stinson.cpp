#include <cstdio>
#include <vector>

#define pb push_back

using namespace std;

int dp[101][21];
vector<vector<int> > requirements;

int main()
{
	int M,N;
	while(true)
	{
	    scanf("%d%d", &M, &N);

        if (M == 0 && N == 0)
	    {
	        break;
        }
        
        for (int i=0; i<M; i++)
        {
            vector<int> temp(2);
            scanf("%d%d", &temp[0], &temp[1]);
            requirements.pb(temp);
        }

        // Base case initialization
        dp[0][0] = 1;
        for (int i=1; i<=N; i++) dp[i][0] = 0;

        for (int i=0; i<=N; i++)
        {
            for (int j=1; j<=M; j++)
            {
                int min = requirements[j-1][0];
                int max = requirements[j-1][1];

                for (int k=i-min; k>=0 && k>=i-max; k--)
                {
                    dp[i][j] += dp[k][j-1];
                }
            }
        }

        printf("%d\n", dp[N][M]);
    }

    return 0;
}
