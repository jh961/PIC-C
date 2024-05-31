#include <18f4550.h>
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#include <lcd.c>
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7,STREAM=pc 1)
#use i2c(master,FAST, scl=PIN_B1, sda=PIN_B0,FORCE_SW)

int dato1=0,dato2=0,x=0,b=0,b1=0,j=5000;
long l1=3522,d=24,dato=24,c=24;
const int voz[]={125,
134,
147,
154,
161,
160,
155,
144,
132,
119,
108,
105,
106,
115,
126,
136,
144,
149,
147,
153,
155,
155,
151,
136,
120,
98,
77,
65,
64,
75,
96,
118,
138,
153,
163,
170,
170,
163,
145,
125,
108,
96,
93,
100,
114,
133,
148,
157,
154,
158,
167,
169,
165,
149,
127,
98,
72,
54,
49,
61,
84,
114,
139,
158,
167,
171,
172,
164,
146,
124,
106,
96,
95,
103,
117,
131,
145,
153,
154,
165,
173,
173,
165,
145,
117,
84,
58,
45,
49,
70,
103,
135,
160,
172,
172,
167,
158,
142,
123,
105,
97,
97,
104,
115,
130,
143,
156,
157,
170,
180,
180,
166,
140,
109,
75,
52,
40,
51,
81,
116,
150,
171,
174,
162,
150,
137,
127,
115,
107,
105,
106,
112,
122,
134,
146,
153,
162,
180,
190,
185,
162,
128,
89,
56,
39,
44,
65,
99,
135,
162,
173,
166,
151,
138,
127,
117,
110,
107,
107,
109,
116,
127,
141,
154,
160,
183,
193,
189,
166,
129,
92,
59,
43,
45,
66,
100,
136,
163,
170,
161,
145,
133,
127,
122,
115,
108,
103,
103,
109,
122,
138,
157,
170,
190,
198,
194,
169,
131,
91,
58,
40,
43,
64,
97,
132,
159,
167,
160,
146,
138,
135,
133,
121,
107,
98,
96,
102,
116,
135,
158,
173,
186,
197,
191,
168,
131,
94,
66,
52,
54,
69,
94,
119,
138,
149,
153,
154,
155,
156,
148,
127,
101,
86,
86,
98,
114,
132,
151,
166,
179,
198,
201,
186,
150,
107,
71,
52,
47,
58,
76,
101,
127,
147,
164,
173,
170,
163,
147,
124,
96,
83,
87,
99,
113,
127,
140,
156,
170,
198,
210,
196,
160,
117,
81,
60,
50,
50,
61,
81,
111,
144,
172,
184,
176,
159,
143,
126,
106,
91,
90,
99,
110,
122,
134,
148,
163,
187,
210,
202,
176,
132,
98,
71,
59,
47,
50,
67,
99,
135,
166,
181,
175,
157,
143,
132,
121,
100,
93,
98,
112,
122,
132,
140,
154,
155,
179,
193,
181,
156,
124,
103,
81,
69,
60,
64,
80,
107,
132,
153,
162,
159,
149,
142,
136,
127,
118,
114,
119,
120,
117,
118,
119,
125,
131,
146,
170,
177,
178,
176,
161,
133,
106,
76,
61,
59,
64,
79,
96,
116,
132,
148,
162,
170,
173,
169,
160,
143,
119,
97,
82,
81,
91,
110,
131,
157,
181,
194,
201,
189,
161,
127,
87,
62,
48,
49,
59,
75,
99,
123,
144,
164,
177,
185,
185,
173,
153,
127,
99,
80,
72,
79,
97,
123,
144,
171,
189,
199,
199,
181,
150,
113,
76,
55,
46,
51,
64,
85,
109,
131,
151,
167,
178,
184,
181,
166,
143,
117,
92,
76,
75,
88,
108,
132,
153,
176,
189,
194,
189,
170,
141,
106,
74,
55,
49,
55,
69,
91,
114,
134,
153,
166,
177,
182,
178,
164,
141,
115,
91,
78,
78,
91,
112,
133,
153,
173,
185,
191,
186,
168,
141,
107,
75,
55,
46,
52,
67,
92,
117,
137,
156,
168,
179,
182,
180,
168,
144,
117,
90,
75,
73,
86,
108,
133,
153,
173,
186,
192,
189,
175,
149,
116,
80,
54,
42,
45,
61,
86,
113,
136,
155,
166,
173,
176,
176,
168,
152,
128,
102,
82,
73,
80,
99,
123,
146,
166,
181,
188,
187,
175,
156,
130,
101,
74,
56,
48,
53,
68,
95,
121,
146,
164,
174,
178,
175,
169,
157,
141,
122,
100,
86,
80,
87,
104,
127,
148,
165,
177,
180,
177,
168,
151,
130,
105,
82,
66,
59,
60,
69,
90,
114,
137,
158,
171,
178,
176,
169,
157,
142,
127,
110,
97,
89,
89,
98,
113,
129,
146,
158,
163,
164,
157,
150,
141,
129,
117,
102,
89,
81,
80,
85,
95,
111,
127,
143,
155,
163,
164,
160,
151,
142,
132,
124,
117,
111,
107,
104,
107,
112,
121,
131,
140,
148,
152,
150,
145,
138,
129,
125,
121,
118,
116,
112,
109,
107,
107,
110,
116,
124,
131,
137,
142,
141,
141,
138,
135,
132,
128,
127,
127,
127,
127,
127,
128,
127,
126,
125,
122,
124,
123,
125,
126,
129,
133,
126,
129,
129,
132,
131,
132,
130,
127,
126,
121,
119,
116,
111,
116,
116,
121,
126,
129,
134,
135,
137,
138,
138,
136,
134,
131,
127,
126,
125,
123,
127,
125,
120,
125,
124,
130,
126,
137,
126,
127,
114,
119,
120,
125,
127,
126,
133,
135,
135,
127,
127,
128,
131,
133,
139,
139,
136,
127,
120,
111,
110,
109,
115,
120,
127,
130,
132,
130,
138,
138,
136,
128,
123,
116,
113,
112,
118,
122,
130,
131,
142,
138,
154,
176,
176,
163,
125,
94,
67,
66,
79,
111,
134,
147,
141,
127,
111,
110,
123,
155,
170,
166,
129,
101,
82,
88,
104,
129,
145,
155,
151,
156,
193,
198,
184,
131,
81,
42,
41,
68,
117,
154,
164,
142,
112,
85,
86,
112,
154,
186,
189,
151,
101,
70,
75,
98,
130,
148,
159,
145,
159,
187,
194,
176,
131,
85,
50,
49,
71,
119,
154,
163,
139,
108,
86,
90,
118,
155,
188,
188,
154,
102,
71,
74,
96,
127,
146,
153,
145,
137,
175,
202,
198,
152,
95,
48,
35,
57,
109,
158,
178,
158,
116,
81,
73,
101,
144,
187,
201,
173,
118,
73,
64,
84,
115,
145,
155,
151,
132,
156,
193,
210,
185,
124,
65,
29,
30,
70,
130,
175,
181,
146,
103,
72,
77,
114,
164,
201,
201,
157,
98,
61,
64,
92,
127,
151,
160,
147,
139,
172,
196,
196,
158,
104,
58,
33,
44,
86,
140,
173,
173,
142,
104,
79,
85,
117,
161,
194,
191,
149,
99,
68,
69,
93,
127,
151,
164,
152,
159,
181,
186,
172,
134,
95,
62,
42,
46,
83,
129,
163,
171,
153,
125,
104,
100,
120,
152,
172,
163,
132,
104,
103,
115,
131,
146,
154,
148,
134,
124,
114,
114,
116,
121,
131,
139,
144,
144,
139,
128,
114,
97,
86,
84,
90,
104,
124,
142,
155,
161,
161,
159,
154,
148,
137,
127,
115,
99,
90,
87,
94,
109,
127,
145,
155,
161,
161,
159,
155,
149,
139,
122,
102,
84,
72,
67,
76,
97,
120,
141,
156,
167,
171,
168,
160,
150,
139,
127,
115,
104,
96,
91,
92,
100,
116,
131,
147,
157,
167,
170,
172,
167,
158,
140,
116,
88,
66,
56,
56,
70,
93,
122,
145,
163,
173,
175,
172,
166,
156,
143,
123,
103,
85,
76,
81,
94,
116,
137,
153,
170,
184,
191,
191,
179,
154,
118,
78,
50,
40,
47,
64,
91,
120,
141,
158,
168,
175,
178,
175,
163,
142,
114,
88,
71,
71,
85,
110,
133,
153,
173,
188,
198,
195,
180,
148,
107,
66,
42,
35,
44,
67,
98,
127,
150,
165,
177,
184,
185,
177,
155,
125,
93,
70,
66,
75,
100,
126,
151,
177,
195,
207,
200,
181,
143,
100,
61,
37,
31,
46,
72,
105,
133,
154,
170,
181,
187,
185,
170,
140,
108,
83,
69,
72,
91,
112,
141,
172,
196,
206,
196,
171,
132,
92,
61,
45,
45,
59,
86,
119,
147,
169,
184,
190,
182,
161,
128,
98,
74,
66,
72,
92,
114,
146,
185,
212,
221,
205,
172,
127,
81,
48,
33,
36,
56,
89,
127,
157,
179,
195,
196,
183,
153,
118,
85,
64,
59,
70,
92,
126,
170,
206,
227,
221,
195,
151,
103,
61,
34,
28,
40,
69,
106,
143,
172,
196,
204,
197,
171,
133,
96,
66,
54,
59,
80,
115,
159,
197,
223,
224,
203,
162,
112,
66,
37,
28,
39,
65,
102,
137,
169,
192,
202,
194,
169,
133,
97,
70,
60,
67,
89,
126,
167,
200,
220,
215,
191,
147,
101,
61,
37,
31,
45,
72,
109,
143,
173,
193,
200,
187,
159,
124,
88,
65,
60,
72,
103,
148,
189,
217,
224,
208,
170,
123,
76,
44,
28,
32,
55,
89,
126,
161,
190,
203,
199,
175,
139,
102,
72,
60,
65,
90,
131,
174,
209,
222,
214,
183,
138,
90,
54,
32,
30,
47,
78,
116,
151,
183,
201,
201,
182,
149,
110,
78,
63,
64,
83,
124,
166,
202,
221,
217,
190,
146,
99,
58,
34,
29,
44,
73,
109,
145,
177,
197,
203,
187,
157,
117,
82,
63,
61,
76,
114,
159,
198,
220,
219,
196,
154,
107,
64,
38,
29,
39,
67,
104,
139,
172,
196,
203,
192,
163,
125,
89,
66,
61,
71,
104,
148,
189,
217,
220,
203,
166,
118,
72,
42,
29,
35,
60,
95,
130,
166,
191,
203,
195,
172,
135,
98,
71,
62,
68,
93,
133,
174,
206,
220,
211,
181,
136,
89,
53,
33,
33,
50,
81,
119,
154,
184,
200,
200,
181,
148,
111,
79,
62,
63,
78,
112,
155,
194,
219,
221,
201,
162,
114,
67,
39,
25,
35,
63,
101,
139,
171,
193,
203,
194,
169,
134,
97,
70,
60,
64,
85,
122,
165,
201,
222,
219,
196,
154,
106,
63,
33,
24,
38,
68,
110,
148,
177,
195,
200,
190,
164,
131,
96,
69,
59,
64,
86,
117,
157,
194,
218,
220,
202,
167,
120,
73,
38,
24,
29,
57,
98,
139,
173,
191,
198,
192,
172,
143,
110,
80,
64,
64,
76,
103,
132,
169,
200,
218,
216,
192,
154,
108,
64,
33,
25,
37,
68,
110,
149,
179,
192,
192,
183,
162,
137,
107,
82,
68,
68,
80,
106,
135,
161,
192,
211,
214,
195,
160,
118,
74,
42,
28,
34,
62,
101,
140,
171,
187,
187,
175,
162,
144,
123,
100,
84,
80,
90,
109,
129,
150,
164,
167,
172,
167,
158,
143,
125,
105,
87,
75,
73,
81,
98,
117,
134,
146,
153,
154,
153,
147,
142,
136,
127,
122,
116,
114,
115,
118,
124,
128,
134,
136,
136,
132,
133,
133,
133,
134,
132,
129,
124,
118,
112,
109,
108,
109,
113,
119,
125,
132,
138,
142,
145,
144,
141,
137,
132,
127,
124,
122,
119,
117,
116,
118,
121,
126,
129,
134,
136,
135,
137,
136,
136,
136,
132,
128,
122,
115,
109,
107,
108,
111,
117,
123,
129,
134,
138,
141,
141,
139,
136,
131,
128,
127,
124,
124,
124,
125,
125,
126,
126,
127,
127,
127,
127,
127,
127,
127,
128,
128,
129,
130,
130,
130,
130,
128,
127,
123,
120,
117,
117,
118,
119,
123,
126,
128,
131,
134,
135,
135,
135,
134,
133,
130,
127,
127,
125,
124,
124,
125,
127,
127,
127,
127,
125,
124,
122,
124,
124,
124,
127,
128,
131,
131,
132,
131,
131,
129,
128,
126,
126,
125,
126,
126,
128,
127,
123,
124,
123,
124,
125,
127,
127,
129,
128,
130,
129,
130,
130,
131,
134,
129,
128,
121,
120,
117,
122,
124,
127,
131,
133,
139,
131,
127,
114,
124,
118,
124,
115,
124,
124,
132,
133,
137,
135,
134,
137,
133,
130,
126,
123,
122,
122,
135,
140,
140,
126,
112,
98,
96,
106,
119,
133,
140,
140,
132,
127,
122,
129,
136,
147,
148,
148,
132,
118,
105,
105,
111,
122,
129,
129,
127,
132,
137,
144,
142,
137,
130,
123,
119,
145,
157,
148,
118,
81,
67,
71,
106,
132,
155,
149,
134,
117,
110,
121,
138,
155,
155,
144,
126,
115,
117,
133,
154,
146,
124,
98,
95,
109,
126,
133,
135,
136,
134,
131,
137,
145,
143,
136,
126,
111,
115,
145,
131,
126,
95,
76,
94,
104,
139,
145,
141,
136,
117,
124,
127,
139,
152,
142,
136,
122,
123,
132,
136,
141,
133,
128,
145,
116,
107,
104,
102,
127,
121,
127,
127,
126,
141,
145,
147,
143,
129,
122,
118,
116,
115,
114,
131,
162,
135,
113,
92,
81,
117,
136,
144,
147,
119,
110,
119,
130,
153,
153,
139,
132,
120,
124,
132,
136,
137,
127,
116,
119,
123,
148,
143,
108,
109,
105,
115,
133,
127,
124,
133,
133,
140,
139,
130,
134,
132,
124,
121,
120,
120,
121,
119,
119,
124,
156,
154,
121,
106,
93,
102,
137,
143,
134,
129,
113,
115,
136,
142,
146,
144,
126,
119,
123,
127,
136,
138,
127,
120,
119,
121,
133,
154,
132,
102,
106,
110,
124,
136,
124,
119,
128,
130,
141,
148,
135,
131,
130,
120,
122,
126,
120,
125,
126,
116,
119,
125,
127,
152,
160,
123,
104,
103,
97,
120,
146,
138,
130,
127,
115,
123,
145,
145,
138,
134,
121,
116,
127,
133,
131,
131,
125,
116,
126,
143,
129,
110,
112,
114,
122,
133,
127,
119,
128,
136,
138,
142,
136,
127,
130,
127,
120,
120,
125,
125,
124,
122,
116,
118,
126,
135,
153,
150,
122,
103,
102,
104,
125,
147,
143,
130,
126,
121,
123,
137,
143,
138,
132,
126,
117,
121,
129,
131,
130,
129,
124,
134,
134,
110,
104,
120,
122,
125,
132,
127,
128,
139,
138,
134,
137,
133,
125,
127,
126,
121,
125,
123,
120,
124,
124,
120,
125,
128,
135,
144,
132,
114,
112,
117,
120,
128,
131,
124,
124,
132,
137,
139,
138,
132,
127,
127,
127,
126,
126,
126,
124,
128,
128,
125,
127,
126,
127,
127,
127,
128,
127,
126,
127,
127,
126,
128,
127,
127,
128,
127,
127,
127,
128,
127,
125,
127,
127,
126,
127,
127,
127,
127,
127,
127,
128,
129,
126,
127,
127,
128,
126,
127,
126,
128,
127,
127,
127,
127,
127,
126,
127,
126,
128,
124,
127,
127,
127,
127,
128,
128,
128,
127,
129,
126,
127,
126,
126,
127,
127,
126,
127,
127,
127,
127,
127,
127,
127,
128,
128,
127,
127,
127,
127,
128,
126,
127,
130,
127,
127,
127,
126,
128,
126,
126,
127,
127,
127,
127,
126,
128,
127,
128,
129,
126,
127,
127,
127,
127,
128,
128,
127,
127,
125,
127,
126,
127,
128,
127,
127,
127,
128,
127,
127,
128,
127,
127,
126,
126,
127,
128,
127,
126,
128,
127,
127,
127,
127,
126,
128,
127,
127,
127,
123,
126,
129,
128,
130,
128,
125,
126,
126,
129,
129,
128,
127,
126,
125,
127,
126,
128,
127,
126,
128,
127,
127,
128,
127,
127,
127,
128,
127,
127,
126,
126,
127,
127,
127,
126,
128,
127,
128,
127,
128,
127,
126,
127,
127,
127,
127,
127,
128,
124,
127,
129,
127,
126,
128,
128,
128,
127,
127,
126,
126,
126,
126,
128,
127,
127,
128,
127,
127,
124,
127,
126,
127,
128,
128,
128,
127,
127,
129,
127,
127,
126,
126,
126,
129,
129,
127,
128,
127,
128,
127,
126,
125,
124,
126,
127,
128,
127,
127,
127,
129,
129,
128,
128,
127,
127,
128,
127,
126,
126,
124,
123,
125,
127,
129,
130,
130,
128,
126,
123,
124,
124,
125,
129,
128,
129,
128,
130,
131,
131,
131,
129,
127,
127,
125,
122,
116,
115,
114,
116,
119,
124,
128,
135,
138,
143,
145,
147,
152,
150,
146,
134,
119,
101,
88,
84,
87,
101,
121,
140,
152,
153,
140,
127,
115,
110,
109,
123,
131,
141,
159,
172,
180,
176,
161,
133,
103,
77,
63,
62,
74,
93,
122,
146,
166,
170,
159,
138,
115,
101,
98,
103,
117,
129,
153,
174,
189,
189,
172,
145,
113,
84,
63,
54,
61,
81,
110,
144,
170,
182,
171,
148,
121,
98,
88,
93,
105,
125,
155,
180,
194,
194,
179,
148,
112,
78,
56,
48,
58,
81,
113,
146,
174,
187,
177,
152,
121,
95,
82,
84,
97,
117,
153,
180,
197,
194,
180,
150,
117,
83,
62,
53,
60,
81,
112,
143,
172,
185,
177,
155,
125,
100,
84,
83,
93,
114,
146,
175,
195,
198,
185,
154,
118,
84,
60,
53,
62,
82,
111,
142,
170,
185,
178,
158,
128,
102,
84,
80,
89,
110,
140,
171,
195,
200,
188,
159,
124,
87,
62,
51,
56,
76,
103,
134,
168,
188,
186,
167,
136,
107,
85,
78,
84,
98,
132,
165,
191,
202,
195,
171,
135,
99,
66,
52,
50,
66,
92,
125,
156,
180,
189,
176,
149,
117,
91,
79,
83,
95,
119,
153,
180,
199,
200,
185,
155,
118,
81,
57,
46,
52,
74,
106,
140,
169,
187,
187,
168,
138,
107,
87,
79,
84,
101,
127,
158,
184,
200,
197,
180,
149,
112,
77,
52,
41,
49,
75,
111,
146,
175,
192,
193,
171,
138,
104,
80,
74,
84,
103,
125,
154,
180,
197,
200,
186,
159,
123,
85,
58,
43,
47,
67,
100,
133,
162,
183,
191,
181,
157,
125,
94,
82,
82,
92,
111,
127,
151,
172,
188,
192,
182,
159,
127,
91,
64,
49,
51,
71,
101,
134,
159,
174,
179,
175,
158,
133,
109,
93,
88,
91,
104,
122,
139,
153,
168,
177,
179,
171,
153,
127,
98,
73,
60,
62,
75,
101,
128,
149,
162,
164,
161,
152,
140,
128,
118,
109,
106,
108,
116,
126,
134,
142,
145,
152,
154,
154,
148,
136,
121,
103,
89,
81,
85,
99,
118,
133,
141,
145,
144,
140,
137,
137,
134,
130,
126,
122,
122,
123,
123,
125,
127,
129,
130,
133,
138,
140,
142,
140,
134,
124,
112,
102,
100,
105,
112,
119,
126,
131,
134,
138,
139,
140,
140,
138,
133,
128,
123,
119,
116,
116,
119,
123,
128,
132,
136,
137,
138,
135,
132,
129,
127,
126,
124,
122,
118,
117,
117,
118,
121,
123,
125,
127,
128,
130,
132,
132,
132,
132,
131,
129,
128,
128,
127,
127,
127,
127,
127,
127,
126,
127,
127,
129,
129,
127,
127,
125,
123,
123,
125,
126,
127,
128,
128,
128,
129,
128,
127,
127,
125,
124,
124,
123,
124,
124,
126,
127,
129,
130,
131,
131,
132,
131,
129,
128,
127,
126,
125,
125,
126,
126,
126,
126,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
126,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
126,
126,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
127,
126,
127,
127,
127,
127,
127,
127,
127,
127,
127,
128,
127,
126,
124,
125,
127,
129,
129,
130,
129,
128,
126,
125,
127,
127,
127,
127,
126,
127,
126,
127,
127,
128,
127,
126,
125,
123,
123,
126,
127,
131,
132,
130,
127,
127,
127,
128,
130,
128,
127,
126,
125,
127,
135,
140,
136,
122,
107,
100,
101,
115,
130,
145,
144,
136,
128,
126,
128,
132,
128,
127,
124,
121,
119,
124,
130,
137,
137,
137,
134,
132,
129,
132,
130,
152,
162,
140,
98,
66,
65,
93,
129,
145,
135,
116,
108,
118,
139,
157,
154,
134,
122,
124,
148,
168,
142,
106,
89,
111,
131,
132,
119,
122,
133,
142,
141,
134,
128,
130,
139,
127,
166,
163,
122,
68,
54,
90,
132,
142,
114,
94,
109,
143,
163,
144,
123,
115,
133,
156,
153,
130,
115,
125,
141,
162,
134,
98,
96,
124,
138,
120,
107,
119,
132,
137,
137,
143,
151,
141,
118,
120,
130,
111,
135,
154,
115,
83,
91,
130,
137,
121,
98,
115,
145,
154,
125,
108,
124,
151,
151,
131,
123,
134,
144,
132,
118,
127,
131,
141,
141,
103,
99,
122,
135,
116,
101,
118,
137,
144,
136,
137,
145,
136,
123,
129,
128,
122,
111,
114,
158,
147,
96,
83,
118,
144,
125,
101,
114,
147,
144,
119,
116,
140,
149,
131,
117,
133,
147,
135,
115,
122,
138,
134,
119,
117,
155,
138,
90,
104,
142,
130,
94,
116,
142,
138,
121,
139,
153,
138,
118,
132,
131,
119,
112,
122,
115,
141,
153,
107,
99,
127,
141,
113,
103,
126,
144,
125,
112,
129,
147,
135,
125,
135,
141,
132,
123,
128,
132,
127,
118,
129,
131,
136,
140,
104,
111,
132,
127,
102,
118,
137,
127,
126,
138,
147,
133,
131,
136,
130,
125,
119,
117,
121,
120,
133,
145,
120,
115,
124,
131,
117,
113,
126,
130,
121,
124,
136,
139,
129,
128,
135,
136,
127,
125,
128,
131,
126,
127,
130,
130,
124,
158,
105,
98,
131,
135,
101,
109,
141,
131,
117,
137,
152,
132,
127,
138,
134,
119,
121,
127,
120,
118,
123,
124,
131,
139,
123,
115,
127,
130,
117,
113,
126,
128,
125,
129,
136,
135,
133,
131,
132,
131,
129,
125,
130,
129,
129,
125,
129,
125,
150,
119,
99,
125,
133,
109,
108,
132,
130,
121,
134,
145,
136,
130,
132,
135,
133,
123,
117,
127,
132,
117,
117,
127,
122,
118,
132,
132,
119,
123,
129,
123,
116,
122,
129,
129,
129,
134,
139,
135,
132,
131,
130,
127,
126,
127,
128,
127,
127,
142,
126,
114,
119,
124,
116,
112,
126,
128,
125,
129,
140,
141,
128,
127,
132,
135,
127,
126,
125,
132,
127,
117,
121,
125,
120,
114,
124,
129,
132,
127,
126,
127,
127,
123,
121,
127,
128,
129,
133,
135,
135,
131,
130,
129,
127,
128,
127,
131,
135,
128,
123,
122,
121,
118,
116,
120,
123,
127,
130,
132,
135,
133,
134,
129,
129,
133,
127,
127,
125,
130,
127,
118,
121,
127,
119,
117,
124,
127,
121,
123,
133,
134,
125,
128,
128,
127,
126,
126,
129,
130,
129,
132,
134,
133,
130,
129,
128,
126,
126,
124,
125,
122,
123,
125,
125,
124,
125,
129,
127,
131,
130,
134,
131,
130,
129,
127,
127,
121,
121,
125,
124,
122,
124,
126,
130,
126,
124,
125,
128,
125,
123,
126,
130,
127,
131,
133,
129,
129,
132,
130,
125,
126,
129,
127,
126,
127,
128,
125,
126,
127,
};
int voz1[1500]={};
char a,eprom[];

#INT_rda
void rda_isr(){
   a = fgetc () ;
   output_high(pin_a5);
   IF (a == '@')
   {
     eprom[0] = a;
   
      FOR (d = 1; d <= 100; d++)
      {
         a = fgetc () ;
         
          
        IF (a == '#')
         {
         break;
         }
       }
   }
} 
  
void main(){
     set_tris_a (0x0f);
     lcd_init();
     enable_interrupts (INT_rda) ;
     enable_interrupts (GLOBAL) ;
     
    lcd_putc("\f");
    lcd_gotoxy (1, 1) ;
    printf (lcd_putc, "AUTOR");
    lcd_gotoxy (1, 2) ;
    printf (lcd_putc, "JAIME DIAZ1");
    delay_ms(1000);
    
    setup_ccp1 (ccp_pwm) ;
    setup_timer_2 (t2_div_by_1, 255, 1) ;
    
 while (true){
 output_low(pin_a5);
   
//////////////////cominicacion con eeprom 
 
if(x==0){
x=1;

     
for(d=0;d<=l1;d++){

   i2c_start();           /// inicio
   i2c_write(0xA2);        ///direccion
   i2c_write(b);          ///direccion
   i2c_write(c);
   i2c_write(voz[d]);
   i2c_stop();
   delay_ms(3);
 

 if((c)>=255){
 b++;
 c=-1;
 }
 
  lcd_putc("\f");
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "numero=%ld %ld",d, c);
   c++;
}
 
  /* 
   i2c_start();           /// inicio
   output_high(pin_a5);
   i2c_write(0xA2);        ///direccion
   i2c_write(0x01);          ///direccion
   i2c_write(dato);
   i2c_write(dato);
   i2c_stop();
   
  */
    lcd_putc("\f");
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "LISTO DATO OK");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "GUARDADO EEPROM");
   delay_ms(1000);
   c=0;
}

///////////////////// lectura de datos  
/*
for(d=0;d<=l1;d++){

   i2c_start();
   i2c_write(0xA2);
   i2c_write(b1);
   i2c_write(dato);
   i2c_start();
   i2c_write(0xA3);
   dato2=voz1[d]=i2c_read(0);
   dato1=voz1[d];
   i2c_stop();
   delay_ms(j);
   
 if((dato)>=255){
 b1++;
 dato=-1;
 }
 lcd_putc("\f");
 lcd_gotoxy (1, 1) ;
 printf (lcd_putc, "DATOg =%ld %u",d,dato1);
 lcd_gotoxy (1, 2) ;
 printf (lcd_putc, "%u",dato2);
 dato++;
  
}
b1=0;
dato=24;


     
   lcd_putc("\f");
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "LISTO");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "EEPROM");
   delay_ms(1000);
 /*  
   lcd_putc("\f");
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "DATO =%ld",c-22);
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "EEPROM =%ld",dato1);
   delay_ms(10);
*/
  
 }
}