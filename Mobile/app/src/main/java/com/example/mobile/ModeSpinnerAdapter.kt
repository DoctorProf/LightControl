package com.example.mobile

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.TextView
import com.example.mobile.retrofit.dto.Mode

class ModeSpinnerAdapter(context: Context, private val modes: List<Mode>) : ArrayAdapter<Mode>(context, 0, modes) {

    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
        return initView(position, convertView, parent)
    }

    override fun getDropDownView(position: Int, convertView: View?, parent: ViewGroup): View {
        return initView(position, convertView, parent)
    }

    private fun initView(position: Int, convertView: View?, parent: ViewGroup): View {
        var view = convertView
        if (view == null) {
            view = LayoutInflater.from(context).inflate(android.R.layout.simple_spinner_item, parent, false)
        }

        val textView = view?.findViewById<TextView>(android.R.id.text1)
        textView?.text = modes[position].name

        return view!!
    }
}