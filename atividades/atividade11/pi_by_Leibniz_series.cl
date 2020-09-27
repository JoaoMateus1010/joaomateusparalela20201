__kernel void pi_Leibniz(__global float* c, int iNumElements) {
		/*
			A solução em questão foi baseada na Série de Leibniz, onde:
			\frac{\pi}{4}=\sum_{n=0}^{\infty}\frac{(-1)^{n}}{2n+1}

			aí eu só multipliquei por 4 no host o cálculo que o device fez.
		*/
	int iGID = get_global_id(0);
	
	if (iGID < iNumElements) {
		c[iGID] = (float)(iGID%2==0?1:-1)/(2*iGID+1);
	}	
}
