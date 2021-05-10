/*operator: +, -, *, /, >>, <<, %, ^, |, ^, ~*/

BI operator~(BI); // Passed
BI operator&(const BI&, const BI&);
BI operator|(const BI&, const BI&);
BI operator^(const BI&, const BI&);

BI& operator+(const BI&, const BI&);
BI& operator-(const BI&, const BI&);
BI& operator*(const BI&, const BI&);
BI& operator/(const BI&, const BI&);
BI& operator%(const BI&, const BI&);

BI& operator>>(const BI&, const int&);
BI& operator<<(const BI&, const int&);

BI& operator>>(const BI&, const BI&);
BI& operator<<(const BI&, const BI&);