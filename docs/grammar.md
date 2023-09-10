# The NiO Grammar

The NiO grammar defines the syntax and structure of NiO programs, guiding developers in creating valid and meaningful scripts within this specialized language.

## Definition

$$
\begin{align*}

&\text{prog} ::= \text{call} \\
&\text{call} ::= \text{ID} \space \text{'('} \space \text{expr} \space \text{')'} \space \text{';'}\\
&\text{expr} ::= \text{term} \space (+ | -) \space \text{term} \\
&\text{term} ::= \text{factor} \space (* \space | \space /  \space) \space \text{factor} \\
&\text{factor} ::=\text{'('} \space \text{expr} \space \text{')'} \space | \space \text{NUM}  \\
&\end{align*}
$$
