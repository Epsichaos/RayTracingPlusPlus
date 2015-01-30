class Point
{
	protected:
		double m_x;
		double m_y;
		double m_z;
	public:
		Point() {
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}
		Point(double x, double y, double z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}
};
