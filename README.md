This repo shares some old hobby code of mine.
The code produces SVGs with embedded scripting, which visualize side-by-side:
1. The compact group of [_p_-adic integers](https://en.wikipedia.org/wiki/P-adic_integer)
2. The discrete [Prüfer _p_-group](https://en.wikipedia.org/wiki/Pr%C3%BCfer_group)

## Example output
The following is the output for _p_=3:
![3-adics](https://github.com/Culter/AdicViz/blob/main/Output/p3.svg)

As embedded in this README file, that graphic is not very interactive.

You can view the SVG file in raw form to get tooltips when you hover over group elements:
https://raw.githubusercontent.com/Culter/AdicViz/refs/heads/main/Output/p3.svg

Better yet, if you download the file to a location that your browser trusts, an interactive script will run.
When you hover over a group element in one group, the other group will be colored according to the appropriate
Pontryagin dual character.

![Highlighting 1/9 in the Prufer group](highlight_one_ninth.png)
![Highlighting 13+27Z in the 3-adic integers](highlight_13_plus_27Z.png)

(More precisely, in the case of the _p_-adic integers, since each group element occupies zero area,
one actually highlights an element of a _finite projection_ of the group,
which turns into a coloring of a _finite subset_ of the Prüfer group.
That's why, in the second screenshot, the outer elements of the Prüfer group remain gray.)

## Details
The embedding of the _p_-adic integers into the plane is implemented in [Integers.cpp](https://github.com/Culter/AdicViz/blob/main/src/Integers.cpp).
I use the solenoidal embedding,
which is due to van Dantzig (1930) and appears sporadically in the dynamical systems literature later.
The best modern reference is TODO

## See also
* https://commons.wikimedia.org/wiki/File:2-adic_integers_with_dual_colorings.svg
* https://commons.wikimedia.org/wiki/File:3-adic_integers_with_dual_colorings.svg
* https://blogs.ams.org/visualinsight/2014/10/01/2-adic-integers/
