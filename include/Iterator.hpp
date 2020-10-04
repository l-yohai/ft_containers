/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:41:33 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/05 03:42:03 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{

class Iterator
{
	private:
		
	public:
		Iterator();
		Iterator(const Iterator &);
		Iterator& operator=(const Iterator &);
		~Iterator();
};

}

#endif