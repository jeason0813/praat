#ifndef _Label_h_
#define _Label_h_
/* Label.h
 *
 * Copyright (C) 1992-2011,2015 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Collection.h"
#include "Function.h"

Thing_define (Autosegment, Function) {
	void v_copy (Daata data_to)
		override;
	bool v_equal (Daata otherData)
		override;
	static Data_Description s_description;
	Data_Description v_description ()
		override { return s_description; }
};

autoAutosegment Autosegment_create (double tmin, double tmax, const char32 *label);
/*
	Function:
		create a new instance of Autosegment.
	Return value:
		the new Autosegment.
	Preconditions:
		tmax > tmin;
		label may be null;
	Postconditions:
		result -> tmin == tmin;
		result -> tmax == tmax;
		if (label)
			result -> name == nullptr;
		else
			result -> name [] == label [];   // 'label' copied into 'name'
*/

Thing_define (Tier, Sorted) {
	static int compare (Any data1, Any data2);
	int (*v_getCompareFunction ()) (Any data1, Any data2)
		override { return compare; }
};

void Tier_init (Tier me, long initialCapacity);

autoTier Tier_create (long initialCapacity);
/*
	Function:
		create a new Tier containing one Autosegment from -1e30 to 1e30.
	Return value:
		the new Tier.
	Postconditions:
		my size == 1;
		my item [1] -> methods == classAutosegment;
		my item [1] -> xmin == -1e30;
		my item [1] -> xmax == 1e30;
		my item [1] -> name == nullptr;
*/

long Tier_timeToIndex (Tier me, double t);
/*
	Return value:
		index, or 0 if the tier is empty or t is very large.
	Postconditions:
		result == 0 || my item [i] -> xmin <= result < my item [i] -> xmax;
*/

Thing_define (Label, Ordered) {
};

autoLabel Label_create (long initialNumberOfTiers);

void Label_init (Label me, long initialNumberOfTiers);

void Label_addTier (Label me);

void Label_suggestDomain (Label me, double *tmin, double *tmax);

#endif
/* End of file Label.h */
