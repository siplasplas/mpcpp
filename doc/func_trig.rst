.. index:: trigonometric functions

Trigonometric Functions
=======================

Since Pythagoras, we know that

.. figure:: /images/Trigonometria_01a.svg
  :width: 400

:math:`a^2 + b^2 = c^2`.

:math:`sin (\alpha) = \frac{a}{c}`.

:math:`cos (\alpha) = \frac{b}{c}`.

:math:`tan (\alpha) = \frac{a}{b}`.

:math:`sec (\alpha) = \frac{c}{a}`.

:math:`csc (\alpha) = \frac{c}{b}`.

:math:`cot (\alpha) = \frac{b}{a}`.


:math:`\alpha = asin (\frac{a}{c})`.

:math:`\alpha = acos( \frac{b}{c})`.

:math:`\alpha = atan (\frac{a}{b})`.


plot(sin(x), x, [-2*pi,2*pi],frame=True)

plot(cos(x), x, [-2*pi,2*pi],frame=True)

plot(tan(x), x, [-pi/2+0.01,pi/2-0.01],frame=True)

plot(tan(x), x, [-1,1],frame=True)

plot(sec(x), x, [-pi/2+0.01,pi/2-0.01],frame=True)

plot(sec(x), x, [-pi/4,pi/4],frame=True)

plot(csc(x), x, [0.01,pi/2],frame=True)

plot(csc(x), x, [pi/4,pi/2],frame=True)

plot(cot(x), x, [0.01,1],frame=True)

plot(cot(x), x, [0.3,1],frame=True

sage: plot(acos(x), x, [-1,1],frame=True)

sage: plot(asin(x), x, [-1,1],frame=True)

sage: plot(atan(x), x, [-10,10],frame=True)

:math:`cos(\alpha)^2 + sin(\alpha)^2 = 1`.

:math:`1 + tan(\alpha)^2 = sec(\alpha)^2`.

:math:`cot(\alpha)^2 + 1 = csc(\alpha)^2`.

sign_sin = sig of sin, sign_cos = sign of cos

:math:`sin(\alpha) = sign_sin \sqrt{1-cos(\alpha)^2} = sign_cos \frac{\tan(\alpha)}{\sqrt{1+tan(\alpha)^2}}`.

:math:`cos(\alpha) = sign_cos \sqrt{1-sin(\alpha)^2} = sign_cos \frac{1}{\sqrt{1+tan(\alpha)^2}}`.

:math:`tan(\alpha) = sign_sin \frac{\sqrt{1-cos(\alpha)^2}}{cos(\alpha)} = sign_cos \frac{sin(\alpha)}{\sqrt{1-sin(\alpha)^2}}`.

:math:`sin(0) = 0`.
:math:`cos(0) = 1`.
:math:`tan(0) = 0`.
:math:`cot(0) = \infty`.

:math:`sin(\frac{\pi}{12}) = \frac{\sqrt{6}-\sqrt{2}}{4}`.

:math:`cos(\frac{\pi}{12}) = \frac{\sqrt{6}+\sqrt{2}}{4}`.

:math:`tan(\frac{\pi}{12}) = 2 - \sqrt{3}`.

:math:`cot(\frac{\pi}{12}) = 2 + \sqrt{3}`.

:math:`sin(\frac{\pi}{10}) = \frac{\sqrt{5}-1}{4}`.
:math:`cos(\frac{\pi}{10}) = \frac{\sqrt{10+2\sqrt{5}}}{4}`.
:math:`tan(\frac{\pi}{10}) = \frac{\sqrt{25-10\sqrt{5}}}{5}`.
:math:`cot(\frac{\pi}{10}) = \sqrt{5+2\sqrt{5}}`.

:math:`sin(\frac{\pi}{8}) = \frac{\sqrt{2-\sqrt{2}}}{2}`.
:math:`cos(\frac{\pi}{8}) = \frac{\sqrt{2+\sqrt{2}}}{2}`.
:math:`tan(\frac{\pi}{8}) = sqrt{2}-1`.
:math:`cot(\frac{\pi}{8}) = sqrt{2}+1`.

:math:`sin(\frac{\pi}{6}) = \frac{1}{2}`.
:math:`cos(\frac{\pi}{6}) = \frac{\sqrt{3}}{2}`.
:math:`tan(\frac{\pi}{6}) = \frac{1}{\sqrt{3}}`.
:math:`cot(\frac{\pi}{6}) = \sqrt{3}`.

:math:`sin(\frac{\pi}{5}) = \frac{\sqrt{10-2\sqrt{5}}}{4}`.
:math:`cos(\frac{\pi}{5}) = \frac{\sqrt{5}+1}{4}`.
:math:`tan(\frac{\pi}{5}) = \sqrt{5-2sqrt{5}}`.
:math:`cot(\frac{\pi}{5}) = \frac{\sqrt{25+10\sqrt{5}}}{5}`.

:math:`sin(\frac{\pi}{4}) = \frac{1}{sqrt{2}}`.
:math:`cos(\frac{\pi}{4}) = \frac{1}{sqrt{2}}`.
:math:`tan(\frac{\pi}{4}) = 1`.
:math:`cot(\frac{\pi}{4}) = 1`.

:math:`sin(\frac{pi}{4}+\alpha) = cos(\frac{pi}{4}-\alpha)`.
:math:`cos(\frac{pi}{4}+\alpha) = sin(\frac{pi}{4}-\alpha)`.
:math:`tan(\frac{pi}{4}+\alpha) = cot(\frac{pi}{4}-\alpha)`.
:math:`cot(\frac{pi}{4}+\alpha) = tan(\frac{pi}{4}-\alpha)`.

:math:`sin(\pi-\alpha) = sin(\alpha)`.
:math:`sin(\pi+alpha) = -sin(\alpha)`.
:math:`sin(-\alpha) = -sin(\alpha)`.

:math:`cos(\pi-\alpha) = -cos(\alpha)`.
:math:`cos(\pi+\alpha) = -cos(\alpha)`.
:math:`cos(-\alpha) = cos(\alpha)`.

:math:`tan(\pi-\alpha) = -tan(\alpha)`.
:math:`tan(\pi+\alpha) = tan(\alpha)`.
:math:`tan(-\alpha) = -tan(\alpha)`.

:math:`cot(\pi-\alpha) = -cot(\alpha)`.
:math:`cot(\pi+\alpha) = cot(\alpha)`.
:math:`cot(-\alpha) = -cot(\alpha)`.

:math:`sin(\frac{\pi}{2}-\alpha) = cos(\alpha)`.
:math:`sin(\frac{\pi}{2}+\alpha) = cos(\alpha)`.
:math:`sin(\frac{3\pi}{2}-\alpha) = -cos(\alpha)`.
:math:`sin(\frac{3\pi}{2}+\alpha) = -cos(\alpha)`.

:math:`cos(\frac{\pi}{2}-\alpha) = sin(\alpha)`.
:math:`cos(\frac{\pi}{2}+\alpha) = -sin(\alpha)`.
:math:`cos(\frac{3\pi}{2}-\alpha) = -sin(\alpha)`.
:math:`cos(\frac{3\pi}{2}+\alpha) = sin(\alpha)`.

:math:`tan(\frac{\pi}{2}-\alpha) = cot(\alpha)`.
:math:`tan(\frac{\pi}{2}+\alpha) = -cot(\alpha)`.
:math:`tan(\frac{3\pi}{2}-\alpha) = cot(\alpha)`.
:math:`tan(\frac{3\pi}{2}+\alpha) = -cot(\alpha)`.

:math:`cot(\frac{\pi}{2}-\alpha) = tan(\alpha)`.
:math:`cot(\frac{\pi}{2}+\alpha) = -tan(\alpha)`.
:math:`cot(\frac{3\pi}{2}-\alpha) = tan(\alpha)`.
:math:`cot(\frac{3\pi}{2}+\alpha) = -tan(\alpha)`.

:math:`sin(\alpha+\beta) = sin(\alpha)cos(\beta)+cos(\alpha)sin(\beta)`.
:math:`sin(\alpha-\beta) = sin(\alpha)cos(\beta)-cos(\alpha)sin(\beta)`.
:math:`cos(\alpha+\beta) = cos(\alpha)cos(\beta)-sin(\alpha)sin(\beta)`.
:math:`cos(\alpha-\beta) = cos(\alpha)cos(\beta)+ sin(\alpha)sin(\beta)`.
