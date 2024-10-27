package com.example.mobile.retrofit

import com.example.mobile.retrofit.dto.Mode
import com.example.mobile.retrofit.dto.Modes
import com.example.mobile.retrofit.dto.Response
import com.example.mobile.retrofit.dto.Settings
import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.Query

interface ApiService {
    @GET("/getSettings")
    fun getSettings(): Call<Settings>

    @GET("/setSettings")
    fun setSettings(@Query("brightness") brightness: Int): Call<Void>

    @GET("/modes")
    fun getModes(): Call<List<Modes>>

    @GET("/mode")
    fun setModeParameter(@Query("modeId") modeId: String): Call<Response>

    @POST("/mode")
    fun addMode(@Body mode: Mode): Call<Void>

    @DELETE("/mode")
    fun deleteMode(@Query("modeId") modeId: String): Call<Void>
}