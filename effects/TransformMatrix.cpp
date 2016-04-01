/**========================================================================================================================**\
	Transform Matrix
\**========================================================================================================================**/


/*--------------------------------------------------------------------------------*\
Function()

Info text
\*--------------------------------------------------------------------------------*/

#include "TransformMatrix.h"
#include "EFFECTS_DEFINES.h"
#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>

namespace proimage
{
	TransformMatrix::TransformMatrix()
	{
		memset((void*)m_matrix, 0, sizeof(double)* 9);
		memset((void*)m_invmatrix, 0, sizeof(double)* 9);

		for (int j = 0; j < 3; j++)
		{
			m_matrix[j][j] = 1;
			m_invmatrix[j][j] = 1;
		}
	}

	TransformMatrix::~TransformMatrix()
	{

	}

	void TransformMatrix::mul(double left[3][3], double right[3][3], double out[3][3])
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				out[j][i] = (left[j][0] * right[0][i]) + (left[j][1] * right[1][i]) + (left[j][2] * right[2][i]);
			}
		}
	}

	void TransformMatrix::set_matrix(double mx[3][3])
	{
		memcpy((void*)m_matrix, (void*)mx, sizeof(double)* 9);
	}
	void TransformMatrix::set_invmatrix(double inv_mx[3][3])
	{
		memcpy((void*)m_invmatrix, (void*)inv_mx, sizeof(double)* 9);
	}
		
	void TransformMatrix::add_matrix(double mx[3][3], bool prepend)
	{
		double out[3][3];
		if (prepend) mul(mx, m_matrix, out);
		else mul(m_matrix, mx, out);
		set_matrix(out);
	}

	// same as add_matrix only from the other side
	void TransformMatrix::add_invmatrix(double mx[3][3], bool prepend)
	{
		double out[3][3];
		if (prepend) mul(m_invmatrix, mx, out);
		else mul(mx, m_invmatrix, out);
		set_invmatrix(out);
	}

	void TransformMatrix::set_matrix(double mx[3][3], double inv_mx[3][3])
	{
		set_matrix(mx);
		set_invmatrix(inv_mx);
	}

	void TransformMatrix::add_matrix(double mx[3][3], double inv_mx[3][3], bool prepend)
	{
		add_matrix(mx, prepend);
		add_invmatrix(inv_mx, prepend);
	}

	void TransformMatrix::get_matrix(double mx[3][3])
	{
		memcpy(reinterpret_cast<void*>(mx), reinterpret_cast<void*>(m_matrix), sizeof(double)* 9);
	}

	void TransformMatrix::get_invmatrix(double invmx[3][3])
	{
		memcpy(reinterpret_cast<void*>(invmx), reinterpret_cast<void*>(m_invmatrix), sizeof(double)* 9);
	}

	void TransformMatrix::add_translation(double x, double y, bool prepend)
	{
		double trans[3][3] = {
			{ 1, 0, x },
			{ 0, 1, y },
			{ 0, 0, 1 },
		};

		double inv_trans[3][3] = {
			{ 1, 0, -x },
			{ 0, 1, -y },
			{ 0, 0, 1 },
		};

		add_matrix(trans, prepend);
		add_invmatrix(inv_trans, prepend);
	}

	void TransformMatrix::add_scaling(double fact_x, double fact_y, bool prepend)
	{
		double scale[3][3] = {
			{ fact_x, 0, 0 },
			{ 0, fact_y, 0 },
			{ 0, 0, 1 },
		};

		double inv_scale[3][3] = {
			{ 1/fact_x, 0, 0 },
			{ 0, 1/fact_y, 0 },
			{ 0, 0, 1 },
		};

		add_matrix(scale, prepend);
		add_invmatrix(inv_scale, prepend);
	}


	void TransformMatrix::add_rotation_rad(double angle, bool prepend)
	{
		add_rotation_rad(angle, 0.0, 0.0, prepend);
	}

	void TransformMatrix::add_rotation(double angle, bool prepend)
	{
		add_rotation_rad(DEGTORAD(angle), prepend);
	}

	void TransformMatrix::add_rotation_rad(double angle, double center_x, double center_y, bool prepend)
	{
		double rot[3][3] = {
			{ std::cos(angle), -std::sin(angle), 0 },
			{ std::sin(angle), std::cos(angle), 0 },
			{ 0, 0, 1 }
		};

		double inv_rot[3][3] = {
			{ std::cos(-angle), -std::sin(-angle), 0 },
			{ std::sin(-angle), std::cos(-angle), 0 },
			{ 0, 0, 1 }
		};

		if ((center_x != 0.0) || (center_y != 0.0))
		{
			double out[3][3];
			double trans_neg[3][3] = {
				{ 1, 0, -center_x },
				{ 0, 1, -center_y },
				{ 0, 0, 1 },
			};
			double trans[3][3] = {
				{ 1, 0, center_x },
				{ 0, 1, center_y },
				{ 0, 0, 1 },
			};

			mul(rot, trans_neg, out);
			mul(trans, out, rot);

			mul(inv_rot, trans_neg, out);
			mul(trans, out, inv_rot);
		}

		add_matrix(rot, prepend);
		add_invmatrix(inv_rot, prepend);
	}

	void TransformMatrix::add_rotation(double angle, double center_x, double center_y, bool prepend)
	{
		add_rotation_rad(DEGTORAD(angle), center_x, center_y, prepend);
	}

	void TransformMatrix::add_shear_x(double shear_x, bool prepend)
	{
		double shearx[3][3] = {
			{ 1, shear_x, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
		};
		double inv_shearx[3][3] = {
			{ 1, -shear_x, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
		};
		add_matrix(shearx, prepend);
		add_invmatrix(inv_shearx, prepend);
	}
	
	void TransformMatrix::add_shear_y(double shear_y, bool prepend)
	{
		double sheary[3][3] = {
			{ 1, 0, 0 },
			{ shear_y, 1, 0 },
			{ 0, 0, 1 }
		};
		double inv_sheary[3][3] = {
			{ 1, 0, 0 },
			{ -shear_y, 1, 0 },
			{ 0, 0, 1 }
		};
		add_matrix(sheary, prepend);
		add_invmatrix(inv_sheary, prepend);
	}

	void TransformMatrix::calc_matrix(double x, double y, double* _x, double* _y)
	{
		calc_matrix(m_matrix, x, y, _x, _y);
	}

	void TransformMatrix::calc_invmatrix(double x, double y, double* _x, double* _y)
	{
		calc_matrix(m_invmatrix, x, y, _x, _y);
	}

	void TransformMatrix::calc_matrix(double mx[3][3], double x, double y, double* _x, double* _y)
	{
		double out[2] = { 0 };
		for (int j = 0; j < 2; j++)
		{
			out[j] = (mx[j][0] * x) + (mx[j][1] * y) + (mx[j][2]);
		}
		*_x = out[0];
		*_y = out[1];
	}

	void TransformMatrix::calc_newsize(double mx[3][3], unsigned int width, unsigned int height, int *offset_x, int *offset_y, unsigned int* new_width, unsigned int* new_height)
	{
		// top left (0,h)
		double tl_x = 0.0;
		double tl_y = 0.0;
		calc_matrix(mx, 0.0, double(height), &tl_x, &tl_y);

		// bottom left (0,0)
		double bl_x = 0.0;
		double bl_y = 0.0;
		calc_matrix(mx, 0.0, 0.0, &bl_x, &bl_y);

		// bottom right (w,0)
		double br_x = 0.0;
		double br_y = 0.0;
		calc_matrix(mx, (double)width, 0.0, &br_x, &br_y);

		// top right (w,h)
		double tr_x = 0.0;
		double tr_y = 0.0;
		calc_matrix(mx, (double)width, (double)height, &tr_x, &tr_y);

		// maximum distance in x is new width
		double min_x = tl_x;
		if (bl_x < min_x) min_x = bl_x;
		if (br_x < min_x) min_x = br_x;
		if (tr_x < min_x) min_x = tr_x;
		double max_x = tl_x;
		if (bl_x > max_x) max_x = bl_x;
		if (br_x > max_x) max_x = br_x;
		if (tr_x > max_x) max_x = tr_x;

		double min_y = tl_y;
		if (bl_y < min_y) min_y = bl_y;
		if (br_y < min_y) min_y = br_y;
		if (tr_y < min_y) min_y = tr_y;
		double max_y = tl_y;
		if (bl_y > max_y) max_y = bl_y;
		if (br_y > max_y) max_y = br_y;
		if (tr_y > max_y) max_y = tr_y;

		min_x = floor(min_x);
		max_x = ceil(max_x);

		min_y = floor(min_y);
		max_y = ceil(max_y);

		*offset_x = (int)min_x;
		*offset_y = (int)min_y;
		*new_width = (unsigned int)(max_x - min_x);
		*new_height = (unsigned int)(max_y - min_y);
	}
}