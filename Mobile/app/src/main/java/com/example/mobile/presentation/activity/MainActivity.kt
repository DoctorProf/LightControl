package com.example.mobile

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.mobile.databinding.MainActivityBinding
import com.example.mobile.retrofit.ApiService
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class MainActivity : AppCompatActivity() {
    private lateinit var binding: MainActivityBinding

    override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            binding = MainActivityBinding.inflate(layoutInflater)
            setContentView(binding.root)

            val retrofit = Retrofit.Builder()
                .baseUrl("http://192.168.1.21:80")
                .addConverterFactory(GsonConverterFactory.create())
                .build()

            val apiService = retrofit.create(ApiService::class.java)
        }
    }