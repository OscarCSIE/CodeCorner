import matplotlib.pyplot as plt
from scipy.stats import binom

n=10
p=0.5
x=range(n+1)
pmf = binom.pmf(x,n,p)
plt.bar(x,pmf, align='center')
plt.xticks(x)
plt.show()