Special Functions
=================

sage: plot(gamma(x), x, [0.1,1],frame=True)

.. figure:: /images/gamma_0.png

sage: plot(gamma(x), x, [-1,0],frame=True)

.. figure:: /images/gamma_1.png

sage: plot(zeta(x), x, [-1,1],frame=True)

.. figure:: /images/zeta.png

sage: plot(erf(x), x, [-2,2],frame=True)

.. figure:: /images/erf.png

sage: plot(erfc(x), x, [-2,2],frame=True)

.. figure:: /images/erfc.png

sage: def eint(x):
....:     return RR(x).eint()

sage: plot(eint, [-4,4],frame=True)

.. figure:: /images/eint.png

sage: plot(log_gamma, [-1,5],frame=True)

.. figure:: /images/lngamma.png

def j0(x):
	return RR(x).j0()

plot(j0, [-20,20],frame=True)

.. figure:: /images/j0.png

def j1(x):
	return RR(x).j1()

plot(j1, [-20,20],frame=True)

.. figure:: /images/j1.png

def y0(x):
	return RR(x).y0()

plot(y0, [-20,20],frame=True)

.. figure:: /images/y0.png

def y1(x):
	return RR(x).y1()

plot(y1, [-20,20],frame=True)

.. figure:: /images/y1.png
